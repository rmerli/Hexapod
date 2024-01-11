#include <Arduino.h>
#include <Transport.h>
#include <PacketSerial.h>
#include <ps5Controller.h>

PacketSerial packetSerial;

void onPacketReceived(const uint8_t *buffer, size_t size);

void setup()
{
  ps5.begin("e8:47:3a:a0:a3:4c");
  Serial.begin(9600);
  Serial2.begin(9600);
  packetSerial.setStream(&Serial2);
  packetSerial.setPacketHandler(&onPacketReceived);
}

Message decoded;
Message msg = {
  .forward = 0,
  .sideway = 0,
  .direction = 0,
  .tilt_x = 0,
  .tilt_y = 0,
  .gait = 0, 
};

uint8_t buffer[sizeof(msg)];

void loop()
{
  packetSerial.update();

  if (packetSerial.overflow())
  {
    Serial.println("Overflow");
  }


  if (ps5.isConnected() == true)
  {
    if (ps5.LStickX())
    {
      msg.sideway = ps5.LStickX();
    }
    if (ps5.LStickY())
    {
      msg.forward = ps5.LStickY();
    }
    if (ps5.RStickX())
    {
      msg.direction = ps5.RStickX();
    }
    if (ps5.RStickY())
    {
      // Serial.printf("Right Stick y at %d", ps5.RStickY());
      /* Serial.print("\n"); */
    }

    memcpy(buffer, &msg, sizeof(msg));
    packetSerial.send(buffer, sizeof(msg));
  }

  delay(50);
}

void onPacketReceived(const uint8_t *buffer, size_t size)
{
  // memcpy(&msg, buffer, size);
  
  // Serial.printf("%d", msg.forward);
  // Serial.println("\n");
}
