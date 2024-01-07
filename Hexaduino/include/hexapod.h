#include <Arduino.h>
#include <actuator.h>
#include <vector.h>
#include <helper.h>


#ifndef hexapod_defined
#define hexapod_defined

    struct IKangles
    {
        float coax;
        float femore;
        float tibia;
    };

    class Leg
    {
    public:
        float coaxAngle;
        float femoreAngle;
        float tibiaAngle;
        bool isMoving = false;

        Vector3 position = {100.0, 0, -200.0};
        Vector3 startPoint = {150.0, -50.0, -200.0};
        Vector3 controlPoints[3];
        bool firstCycle = true;
        float progress;
        LegStatus status; 

        Leg(float coaxAngle, float femoreAngle, float tibiaAngle);
        Leg();

        void initActuators(int coaxPin, int femorePin, int tibiaPin);
        void move(int speed);
        void setJointsAngles(IKangles angles);

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
        void walk();
        void stop();
        void setGait(Gait gait);
        Vector2 carCommand = {0,0};
    private:
        float cycleDuration = 10000;
        float speed = 50;
        float direction = 1;
        float maxSpeed = 200;
        
        Vector3 standPos = {150.0, 0, -200.0};
        Vector3 target = {150.0, 50.0, -200.0};
        Vector3 midPos = {150.0, 0, -125.0};
        Vector3 startPos = {150.0, -50.0, -200.0};
        
        Vector3 lifting[3]{startPos, midPos, target};
        Vector3 pushing[3]{target, standPos, startPos};

        Vector3 firstStepLifting[3]{standPos, {standPos.x, (target.y - standPos.y)/2, midPos.z}, target};
        Vector3 firstStepPushing[3]{standPos, {standPos.x, (startPos.y - standPos.y)/2, standPos.z}, startPos};

        float progressBreakpoint = 0.5;


        Gait gait = TRI;
        Status status = STANDING;
        Status prevStatus = STANDING;

        void setControlPoints(Leg& leg, Vector3 controlPoints[]);
        void setStartPoint(Leg& leg); 
        void initGait();
        void initStopSequence();
        void planLegsPath();
        void updateLegsPosition();
        void checkProgress();
        void updateProgress();
        void updateSpeed();

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
