#include <actuator.h>

// constructor
Actuator::Actuator(HardwareSerial *serial,int servoId, int min, int max)
{
    Actuator::servo = new SerialServo(serial, servoId);
    Actuator::servo->setMin(min);
    Actuator::servo->setMax(max);
};

void Actuator::move(float angle, float offset, int speed = 1000)
{
    Actuator::servo->write(angle + offset, speed);
};
