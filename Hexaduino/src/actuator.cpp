#include <header.h>

// constructor
Actuator::Actuator(int servoPin)
{
    Actuator::servo = new Servo();
    Actuator::servo->attach(servoPin, Actuator::min, Actuator::max);
};

void Actuator::move(float angle, float offset)
{
    Actuator::servo->writeMicroseconds(Actuator::angleToMicroseconds(angle + offset));
    delay(15);
};

int Actuator::angleToMicroseconds(float angle)
{
    float val = Actuator::min + (((Actuator::max - Actuator::min) / 180.0) * angle);
    return (int)val;
};