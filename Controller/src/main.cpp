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

uint8_t buffer[20];

void loop()
{
  packetSerial.update();

  if (packetSerial.overflow())
  {
    Serial.println("Overflow");
  }

  Message msg;

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
      // Serial.printf("Right Stick y at %d\n", ps5.RStickY());
    }

    memcpy(buffer, &msg, sizeof(msg));
    packetSerial.send(buffer, sizeof(msg));
  }

  delay(50);
}

void onPacketReceived(const uint8_t *buffer, size_t size)
{
  Serial.write(buffer, size);
}