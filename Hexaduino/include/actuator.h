#include <serial_servo.h>

#ifndef actuator_defined
#define actuator_defined
class Actuator
{
public:
    int min = 96;
    int max = 4000;

    Actuator(HardwareSerial *serial, int servoId, int min, int max);
    void move(float angle, float offset, int speed);

private:
    SerialServo *servo;
};
#endif
