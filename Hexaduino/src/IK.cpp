#include <header.h>
void calculateIKLeg(Leg *leg, Vector3 pos)
{
  float x = pos.x;
  float y = pos.y;
  float z = pos.z;

  float r1 = sqrt(pow(x, 2) + pow(y, 2));
  float r2 = z;
  float r3 = sqrt(pow(r1, 2) + pow(r2, 2));

  float phi1 = acos((pow(r3, 2) + pow(femore_length, 2) - pow(tibia_length, 2)) / (2 * r3 * femore_length));
  float phi2 = acos((pow(tibia_length, 2) + pow(femore_length, 2) - pow(r3, 2)) / (2 * tibia_length * femore_length));
  float phi3 = atan(r2 / r1);

  while (leg->isMoving)
  {
  }

  leg->coaxAngle = atan(y / x) * (180 / PI);
  leg->femoreAngle = (phi3 + phi1) * (180 / PI);
  leg->tibiaAngle = (PI - phi2) * (180 / PI);
}