#include <actuator.h>

// constructor
Actuator::Actuator(int servoId, int min, int max)
{
    Actuator::servo = new SerialServo(&Serial2, servoId);
    Actuator::servo->setMin(min);
    Actuator::servo->setMax(max);
};

void Actuator::move(float angle, float offset)
{
    Actuator::servo->write(angle + offset);
};