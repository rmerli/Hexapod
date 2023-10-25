#include <header.h>

#define servo_max 2350
#define servo_min 400

Vector3 startPos = {150.0, 50.0, -150.0};
Vector3 target = {150.0, -50.0, -150.0};
Vector3 currentPos = {0.0, 0.0, 0.0};

Hexapod hexapod;

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

void setup()
{
  Serial.begin(9600);
  hexapod.moveLeg(0, startPos);
  controlPoints[0] = startPos;
  controlPoints[1] = {150, (startPos.y + target.y) / 2, -70};
  controlPoints[2] = target;

  delay(1000);
}

bool up = true;
float speed = 0.0003;
int points = 3;

void loop()
{
  if (t >= 1)
  {
    if (up)
    {
      controlPoints[0] = target;
      controlPoints[1] = {150, (startPos.y + target.y) / 2, startPos.z};
      controlPoints[2] = startPos;
      points = 3;
      up = false;
    }
    else
    {
      controlPoints[0] = startPos;
      controlPoints[1] = {150, (startPos.y + target.y) / 2, -70};
      controlPoints[2] = target;
      up = true;
      points = 3;
    }
    t = 0;
  }
  hexapod.moveLeg(0, GetPointOnBezierCurve(controlPoints, points, t));
  t += speed;
}