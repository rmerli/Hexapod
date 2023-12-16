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
    void move(int speed);

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
    void update();

private:
    Vector3 standPos = {200.0, 0, -200.0};
    Vector3 startPos = {200.0, 100.0, -200.0};
    Vector3 target = {200.0, -100.0, -200.0};
    
    void moveLeg(int leg, Vector3 pos, int speed);
    const byte right_front_coax_pin = 0x01;
    const byte right_front_femore_pin = 0x02;
    const byte right_front_tibia_pin = 0x03;

    const byte right_middle_coax_pin = 0x0b;
    const byte right_middle_femore_pin = 0x0c;
    const byte right_middle_tibia_pin = 0x0d;

    const byte right_back_coax_pin = 0x15;
    const byte right_back_femore_pin = 0x16;
    const byte right_back_tibia_pin = 0x17;

    const byte left_front_coax_pin = 0x1f;
    const byte left_front_femore_pin = 0x20;
    const byte left_front_tibia_pin = 0x21;

    const byte left_middle_coax_pin = 0x29;
    const byte left_middle_femore_pin = 0x2a;
    const byte left_middle_tibia_pin = 0x2b;

    const byte left_back_coax_pin = 0x33;
    const byte left_back_femore_pin = 0x34;
    const byte left_back_tibia_pin = 0x35;
};
#endif