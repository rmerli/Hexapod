#include <hexapod.h>
#include <IK.h>
#include <helper.h>
// constructor
Leg::Leg(float coaxAngle, float femoreAngle, float tibiaAngle)
{
    Leg::coaxAngle = coaxAngle;
    Leg::femoreAngle = femoreAngle;
    Leg::tibiaAngle = tibiaAngle;
}

Leg::Leg()
{
    Leg::coaxAngle = 0;
    Leg::femoreAngle = 0;
    Leg::tibiaAngle = 0;
}

void Leg::initActuators(int coaxPin, int femorePin, int tibiaPin)
{
    Leg::coaxJoint = new Actuator(coaxPin, 340, 2340);
    Leg::femoreJoint = new Actuator(femorePin, 340, 2340);
    Leg::tibiaJoint = new Actuator(tibiaPin, 340, 2340);
}

void Leg::move(int speed = 1000)
{
    Leg::coaxJoint->move(Leg::coaxAngle, 90, speed);
    Leg::femoreJoint->move(Leg::femoreAngle, 100, speed);
    Leg::tibiaJoint->move(Leg::tibiaAngle, 60, speed);
}

Hexapod::Hexapod()
{
    for (int i = 0; i < 6; i++)
    {
        Hexapod::legs[i] = new Leg();
    }

    Hexapod::legs[0]->initActuators(right_front_coax_pin, right_front_femore_pin, right_front_tibia_pin);
    Hexapod::legs[1]->initActuators(right_middle_coax_pin, right_middle_femore_pin, right_middle_tibia_pin);
    Hexapod::legs[2]->initActuators(right_back_coax_pin, right_back_femore_pin, right_back_tibia_pin);
 
    Hexapod::legs[3]->initActuators(left_front_coax_pin, left_front_femore_pin, left_front_tibia_pin);
    Hexapod::legs[4]->initActuators(left_middle_coax_pin, left_middle_femore_pin, left_middle_tibia_pin);
    Hexapod::legs[5]->initActuators(left_back_coax_pin, left_back_femore_pin, left_back_tibia_pin);

    Hexapod::moveLeg(0,Hexapod::standPos,2000);
    Hexapod::moveLeg(1,Hexapod::standPos,2000);
    Hexapod::moveLeg(2,Hexapod::standPos,2000);
    Hexapod::moveLeg(3,Hexapod::standPos,2000);
    Hexapod::moveLeg(4,Hexapod::standPos,2000);
    Hexapod::moveLeg(5,Hexapod::standPos,2000);
};

void Hexapod::update()
{
    // Hexapod::moveLeg(0, Hexapod::standPos, 1000);
}

void Hexapod::moveLeg(int leg, Vector3 pos, int speed = 1000)
{
    // Serial.println(pos.x);
    // Serial.println(pos.y);
    // Serial.println(pos.z);
    calculateIKLeg(Hexapod::legs[leg], pos);
    Hexapod::legs[leg]->move(speed);
}