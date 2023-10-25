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
    const int right_front_coax_pin = 24;
    const int right_front_femore_pin = 26;
    const int right_front_tibia_pin = 28;
};