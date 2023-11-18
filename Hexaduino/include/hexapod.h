#include <Arduino.h>
#include <actuator.h>
#include <vector.h>
#ifndef hexapod_defined
#define hexapod_defined
class Leg
{
public:
    float coaxAngle;
    float femoreAngle;
    float tibiaAngle;
    bool isMoving = false;

    Leg(float coaxAngle, float femoreAngle, float tibiaAngle);
    Leg();

    void initActuators(int coaxPin, int femorePin, int tibiaPin);
    void move();

private:
    Actuator *coaxJoint;
    Actuator *femoreJoint;
    Actuator *tibiaJoint;
};

class Hexapod
{
public:
    Leg *legs[6];

    Hexapod();

    void moveLeg(int leg, Vector3 pos);

private:
    const byte right_front_coax_pin = 0x01;
    const int right_front_femore_pin = 0x02;
    const int right_front_tibia_pin = 0x03;
};
#endif