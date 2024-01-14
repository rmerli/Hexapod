#include <Arduino.h>
#include <Transport.h>
#include <ArduinoCRSF.h>
#include <PacketSerial.h>

#define PIN_RX 5
#define PIN_TX 18
#define CRSF_FORWARD 3
#define CRSF_SIDEWAY 2
#define CRSF_DISTANCE_GROUND 1
#define CRSF_MODE 6
#define CRSF_MIN 1000
#define CRSF_DISTANCE_GROUND 1
#define CRSF_MAX 2000
#define HEXAPOD_COMMAND_MAX 100
#define HEXAPOD_COMMAND_MIN -100
#define HEXAPOD_COMMAND_ZERO 0


HardwareSerial crsfSerial(1);
ArduinoCRSF crsf;

PacketSerial packetSerial;

Message msg = {
  .forward = 0,
  .sideway = 0,
  .distanceFromGround = 0,
  .tilt_x = 0,
  .tilt_y = 0,
  .mode = 0,
  .gait = 0,
};

void sendMessage(Message msg); 
void parseInputIntoMessage(ArduinoCRSF inputSerial, Message *message); 
void resetMessage(Message *message);

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
    // resetMessage(&msg);
    return;
  }

  if (!crsf.isLinkUp()) {
    // resetMessage(&msg);
    return;
  }

  parseInputIntoMessage(crsf, &msg);
  msg.gait = 0;
  // Serial.println(msg.forward);
  // Serial.println(msg.sideway);
  sendMessage(msg);
}

void parseInputIntoMessage(ArduinoCRSF inputSerial, Message *message) {
  int forward = inputSerial.getChannel(CRSF_FORWARD);
  int sideway = inputSerial.getChannel(CRSF_SIDEWAY);
  int distanceFromGround = inputSerial.getChannel(CRSF_DISTANCE_GROUND);
  int mode = inputSerial.getChannel(CRSF_MODE);

  if (mode < ((CRSF_MAX - CRSF_MIN)/3) + CRSF_MIN) {
    message->mode = 0;
  }else {
    message->mode = 1;
  }

  if (forward > CRSF_MAX) {
    forward = CRSF_MAX;
  }

  if (forward < CRSF_MIN) {
    forward = CRSF_MIN;
  }

  if (sideway > CRSF_MAX) {
    sideway = CRSF_MAX;
  }
  if (sideway < CRSF_MIN) {
    sideway = CRSF_MIN;
  }

  if (distanceFromGround > CRSF_MAX) {
    distanceFromGround = CRSF_MAX;
  }

  if (distanceFromGround < CRSF_MIN) {
    distanceFromGround = CRSF_MIN;
  }

  message->forward = map(forward, CRSF_MIN, CRSF_MAX, HEXAPOD_COMMAND_MIN, HEXAPOD_COMMAND_MAX);
  message->sideway = map(sideway, CRSF_MIN, CRSF_MAX, HEXAPOD_COMMAND_MIN, HEXAPOD_COMMAND_MAX);
  message->distanceFromGround = map(distanceFromGround, CRSF_MIN, CRSF_MAX, HEXAPOD_COMMAND_ZERO, HEXAPOD_COMMAND_MAX);
}

void resetMessage(Message *message) {
  message->forward = 0;
  message->sideway = 0;
  message->distanceFromGround = 0;
  message->translateX = 0;
  message->translateY = 0;
  message->tilt_x = 0;
  message->tilt_y = 0;
  message->gait = 0; 
  message->mode = 0; 
}



void sendMessage(Message msg) {
  memcpy(buffer, &msg, sizeof(msg));
  packetSerial.send(buffer, sizeof(msg));
}

void onPacketReceived(const uint8_t *buffer, size_t size)
{
  // memcpy(&msg, buffer, size);
  //
  // Serial.printf("forward: %d ", msg.forward);
  // Serial.printf("sideway: %d ", msg.sideway);
  // Serial.printf("mode: %d ", msg.mode);
  // Serial.printf("gait: %d", msg.gait);
  // Serial.println();
}
