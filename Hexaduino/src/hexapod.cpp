#include <header.h>

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
    Leg::coaxJoint = new Actuator(coaxPin);
    Leg::femoreJoint = new Actuator(femorePin);
    Leg::tibiaJoint = new Actuator(tibiaPin);
}

void Leg::move()
{
    Leg::isMoving = true;
    Leg::coaxJoint->move(Leg::coaxAngle, 90);
    Leg::femoreJoint->move(Leg::femoreAngle, 100);
    Leg::tibiaJoint->move(Leg::tibiaAngle, 60);
    Leg::isMoving = false;

    // Leg::coaxJoint->move(0, 90);
    // Leg::femoreJoint->move(0, 100);
    // Leg::tibiaJoint->move(0, 60);
}

Hexapod::Hexapod()
{
    for (int i = 0; i < 5; i++)
    {
        Hexapod::legs[i] = new Leg();
    }

    Hexapod::legs[0]->initActuators(right_front_coax_pin, right_front_femore_pin, right_front_tibia_pin);

    // Hexapod::leg[1]->initActuators(right_front_coax_pin, right_front_femore_pin, right_front_tibia_pin);
    // Hexapod::leg[2]->initActuators(right_front_coax_pin, right_front_femore_pin, right_front_tibia_pin);
    // Hexapod::leg[3]->initActuators(right_front_coax_pin, right_front_femore_pin, right_front_tibia_pin);
    // Hexapod::leg[4]->initActuators(right_front_coax_pin, right_front_femore_pin, right_front_tibia_pin);
    // Hexapod::leg[5]->initActuators(right_front_coax_pin, right_front_femore_pin, right_front_tibia_pin);
};

void Hexapod::moveLeg(int leg, Vector3 pos)
{
    // Serial.println(pos.x);
    // Serial.println(pos.y);
    // Serial.println(pos.z);
    calculateIKLeg(Hexapod::legs[leg], pos);
    Hexapod::legs[leg]->move();
}