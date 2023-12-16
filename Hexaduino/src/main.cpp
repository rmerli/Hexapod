#include <Arduino.h>
#include <vector.h>
#include <hexapod.h>

#define servo_max 2350
#define servo_min 400

Vector3 startPos = {200.0, 100.0, -200.0};
Vector3 target = {200.0, -100.0, -200.0};
Vector3 currentPos = {0.0, 0.0, 0.0};

Hexapod *hexapod;



float t = 0;
Vector3 controlPoints[3];
int lastExec = 0;

void setup()
{
  Serial2.begin(115200);
  hexapod = new Hexapod();
  // hexapod->moveLeg(0, startPos);
  // controlPoints[0] = startPos;
  // controlPoints[1] = {200, (startPos.y + target.y) / 2, -150};
  // controlPoints[2] = target;
  lastExec = millis();
  delay(1000);
}

bool up = true;
float speed = 0.003;
int points = 3;

void loop()
{

  // if (t >= 1)
  // {
  //   if (up)
  //   {
  //     controlPoints[0] = target;
  //     controlPoints[1] = {200, (startPos.y + target.y) / 2, startPos.z};
  //     controlPoints[2] = startPos;
  //     points = 3;
  //     up = false;
  //   }
  //   else
  //   {
  //     controlPoints[0] = startPos;
  //     controlPoints[1] = {200, (startPos.y + target.y) / 2, -150};
  //     controlPoints[2] = target;
  //     up = true;
  //     points = 3;
  //   }
  //   t = 0;
  // }

  hexapod->update();
  delay(1000);

  // t += speed;

  lastExec = millis();
}