class Actuator
{
public:
    int min = 400;
    int max = 2350;

    Actuator(int servoPin);
    Actuator();
    int angleToMicroseconds(float angle);
    void move(float angle, float offset);

private:
    Servo *servo;
};
