#include <serial_servo.h>

#ifndef actuator_defined
#define actuator_defined
class Actuator
{
public:
    int min = 96;
    int max = 4000;

    Actuator(int servoId, int min, int max);
    void move(float angle, float offset);

private:
    SerialServo *servo;
};
#endif