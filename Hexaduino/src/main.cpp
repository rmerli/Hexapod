#include <Arduino.h>
#include <vector.h>
#include <hexapod.h>

#define servo_max 2350
#define servo_min 400

Vector3 startPos = {200.0, 100.0, -200.0};
Vector3 target = {200.0, -100.0, -200.0};
Vector3 currentPos = {0.0, 0.0, 0.0};

Hexapod *hexapod;

int binomialCoefficient(int n, int k)
{
  int result = 1;

  // Calculate the binomial coefficient using the formula:
  // (n!) / (k! * (n - k)!)
  for (int i = 1; i <= k; i++)
  {
    result *= (n - (k - i));
    result /= i;
  }

  return result;
}

Vector3 GetPointOnBezierCurve(Vector3 *points, int numPoints, float t)
{
  Vector3 pos;

  for (int i = 0; i < numPoints; i++)
  {
    float b = binomialCoefficient(numPoints - 1, i) * pow(1 - t, numPoints - 1 - i) * pow(t, i);
    pos.x += b * points[i].x;
    pos.y += b * points[i].y;
    pos.z += b * points[i].z;
  }

  return pos;
}

float t = 0;
Vector3 controlPoints[3];
int lastExec = 0;

void setup()
{
  Serial2.begin(115200);
  hexapod = new Hexapod();
  hexapod->moveLeg(0, startPos);
  controlPoints[0] = startPos;
  controlPoints[1] = {200, (startPos.y + target.y) / 2, -150};
  controlPoints[2] = target;
  lastExec = millis();
  delay(1000);
}

bool up = true;
float speed = 0.003;
int points = 3;

void loop()
{

  if (t >= 1)
  {
    if (up)
    {
      controlPoints[0] = target;
      controlPoints[1] = {200, (startPos.y + target.y) / 2, startPos.z};
      controlPoints[2] = startPos;
      points = 3;
      up = false;
    }
    else
    {
      controlPoints[0] = startPos;
      controlPoints[1] = {200, (startPos.y + target.y) / 2, -150};
      controlPoints[2] = target;
      up = true;
      points = 3;
    }
    t = 0;
  }

  hexapod->moveLeg(0, GetPointOnBezierCurve(controlPoints, points, t));

  t += speed;

  lastExec = millis();
}