#include <Arduino.h>
#include <Transport.h>
#include <ArduinoCRSF.h>
#include <PacketSerial.h>

#define PIN_RX 5
#define PIN_TX 18

HardwareSerial crsfSerial(1);
ArduinoCRSF crsf;

PacketSerial packetSerial;

Message decoded;
Message msg = {
  .forward = 0,
  .sideway = 0,
  .direction = 0,
  .tilt_x = 0,
  .tilt_y = 0,
  .gait = 0, 
};

void onPacketReceived(const uint8_t *buffer, size_t size);
void printChannels();

void setup()
{
  Serial.begin(9600); 
  Serial2.begin(9600);

  packetSerial.setStream(&Serial2);
  packetSerial.setPacketHandler(&onPacketReceived);

  crsfSerial.begin(CRSF_BAUDRATE, SERIAL_8N1, PIN_RX, PIN_TX);

  if (!crsfSerial) while (1) Serial.println("Invalid crsfSerial configuration");
  crsf.begin(crsfSerial);
}


uint8_t buffer[sizeof(msg)];

void loop()
{
  packetSerial.update();
  crsf.update();

  if (packetSerial.overflow())
  {
    Serial.println("Overflow");
  }

  if (!crsf.isLinkUp()) {
    Serial.println("Failsafe");
    return;
  }

  int forward = crsf.getChannel(3);
  int sideway = crsf.getChannel(2);

  if (forward > 2000) {
    forward = 2000;
  }
  if (forward < 1000) {
    forward = 1000;
  }

  if (sideway > 2000) {
    sideway = 2000;
  }
  if (sideway < 1000) {
    sideway = 1000;
  }

  msg.forward = map(forward, 1000, 2000, -100, 100);
  msg.sideway = map(sideway, 1000, 2000, -100, 100);

  // Serial.println(msg.forward);
  // Serial.println(msg.sideway);

  memcpy(buffer, &msg, sizeof(msg));
  packetSerial.send(buffer, sizeof(msg));

}

void onPacketReceived(const uint8_t *buffer, size_t size)
{
  memcpy(&msg, buffer, size);
  
  // Serial.printf("%d", msg.forward);
  // Serial.println("\n");
}

void printChannels()
{
  //1 thr, 2 roll, 3 pitch, 4 yaw
  for (int ChannelNum = 1; ChannelNum <= 4; ChannelNum++)
  {
    Serial.print(crsf.getChannel(ChannelNum));
    Serial.print(", ");
  }
  Serial.println(" ");
}
