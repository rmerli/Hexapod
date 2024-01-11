#include <Arduino.h>
#include <vector.h>
#include <hexapod.h>
#include <Transport.h>
#include <PacketSerial.h>

#define servo_max 2350
#define servo_min 400

PacketSerial packetSerial;
Message msg = {
  .forward = 0,
  .sideway = 0,
  .direction = 0,
  .tilt_x = 0,
  .tilt_y = 0,
  .gait = 0, 
};

bool isConnected = false;

Hexapod *hexapod;

int lastExec = 0;
int started = 0;

Command command = {
  .x = 0,
  .y = 0,
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

  started = millis();
  delay(1000);
  hexapod->walk();
}

void loop()
{
  packetSerial.update();

  if (packetSerial.overflow())
  {
    Serial.println("Overflow");
  }

  hexapod->setCommand(command);
  hexapod->update();
}

void onPacketReceived(const uint8_t *buffer, size_t size)
{
  memcpy(&msg, buffer, size);
  command.x = msg.sideway;
  command.y = msg.forward;

  // uint8_t replyBuffer[sizeof(msg)];
  // memcpy(replyBuffer, &msg, sizeof(msg));
  // packetSerial.send(buffer, sizeof(msg));
}
