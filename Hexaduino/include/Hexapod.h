#include <Arduino.h>
#include <Actuator.h>
#include <Vector.h>
#include <Helper.h>
#include <Enums.h>

#ifndef hexapod_defined
#define hexapod_defined

    struct Command {
        int x;
        int y;
        uint32_t lastCommandAt;
        uint32_t lastZeroCommand;
    };

    struct IKangles
    {
        float coax;
        float femore;
        float tibia;
    };

    void resetCommand(Command *com);

    class Leg
    {
    public:
        Leg(float coaxAngle, float femoreAngle, float tibiaAngle);
        Leg();    
        int strideMirror = 1; 
        int coaxRotated = 0; 
        int coaxOffsetAngle = 45; 
        void move(int speed);
        void initActuators(int coaxPin, int femorePin, int tibiaPin, HardwareSerial *serial);
        void setJointsAngles(IKangles angles);
        Vector3 position = {100.0, 0, -200.0};
        Vector3 startPoint = {150.0, -50.0, -200.0};

        float progress;
        LegStatus status; 

    private:
        Actuator *coaxJoint;
        Actuator *femoreJoint;
        Actuator *tibiaJoint;

        float coaxAngle;
        float femoreAngle;
        float tibiaAngle;
   };

    class Hexapod
    {
    public:
        Hexapod(HardwareSerial *serial);
        void update();
        void walk();
        void stop();
        void setGait(int gait);
        void setMode(int mode);
        void setCommand(Command com);
    private:
        Leg *legs[6];

        float cycleDuration = 10000;
        float progressBreakpoint = 0.5;
        float speed = 50;
        int servoSpeed = 500;
        float maxSpeed = 400;
        const int MAX_COMMAND = 100;   
        Command command = {.x = 0, .y = 0, .lastCommandAt = 0, .lastZeroCommand = 0};
        Vector3 standPos = {150.0, 0, -200.0};
        Gait gait = TRI;
        Mode mode = CAR;
        Status status = STANDING;
        Status prevStatus = STANDING;
        int coaxOffset = 45;

        void setControlPoints(Leg& leg, Vector3 controlPoints[]);
        void setStartPoint(Leg& leg); 
        void initGait();
        void initStopSequence();
        void planLegsPath();
        void planStandingMovements();
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
