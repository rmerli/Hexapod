#include <header.h>

#define servo_max 2350
#define servo_min 400

Vector3 startPos = {200.0, 0.0, 0.0};
Vector3 target = {200.0, -150.0, 0.0};
Vector3 currentPos = {0.0, 0.0, 0.0};

Hexapod hexapod;

void setup()
{
  // Serial.begin(9600);
  hexapod.moveLeg(0, startPos);
  currentPos = startPos;
  delay(1000);
}

void loop()
{
  if (abs(abs(currentPos.y) - abs(target.y)) < 0.5)
  {
    target.y = target.y * -1;
  }

  currentPos = lerp(currentPos, target, 0.20);
  hexapod.moveLeg(0, currentPos);
}