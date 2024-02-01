#include <Arduino.h>
#include <Vector.h>
#include <Hexapod.h>
#include <Transport.h>
#include <PacketSerial.h>

#define servo_max 2350
#define servo_min 400

PacketSerial packetSerial;

Hexapod *hexapod;

Message msg = {
  .forward = 0,
  .sideway = 0,
  .distanceFromGround = 0,
  .translateX = 0,
  .translateY = 0,
  .tilt_x = 0,
  .tilt_y = 0,
  .mode = 0, 
  .gait = 0, 
};

Command command = {
  .x = 0,
  .y = 0,
  .lastCommandAt = 0,
  .lastZeroCommand = 0,
};

void setup()
{
  //communication serial
  Serial1.begin(9600);
  packetSerial.setStream(&Serial1);
  packetSerial.setPacketHandler(&onPacketReceived);
  //servo serial
  Serial2.begin(115200);
  hexapod = new Hexapod(&Serial2);
  delay(2000);
  // hexapod->walk();
}

void loop()
{
    packetSerial.update();

  if (packetSerial.overflow())
  {
    command.x = 0;
    command.y = 0;
    return;
  }

  hexapod->setMode(msg.mode);
  hexapod->setCommand(command);
  hexapod->setGait(msg.gait);
  hexapod->update();
}

void resetCommand(Command *com) {
  com->x = 0; 
  com->y = 0; 
  com->lastCommandAt = -1;
  com->lastZeroCommand = -1;
}

void onPacketReceived(const uint8_t *buffer, size_t size)
{
  memcpy(&msg, buffer, size);
  command.x = msg.sideway;
  command.y = msg.forward;
  command.lastCommandAt = millis();
  // uint8_t replyBuffer[sizeof(msg)];
  // memcpy(replyBuffer, &msg, sizeof(msg));
  // packetSerial.send(buffer, sizeof(msg));
}
