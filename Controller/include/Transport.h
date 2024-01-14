#include <Arduino.h>
enum Gait {TRI, WAVE};
enum Mode {CAR, TRANS};
struct Message
{
    int forward;
    int sideway;
    int distanceFromGround;
    int translateX;
    int translateY;
    int tilt_x;
    int tilt_y;
    int mode; 
    int gait; 
};

void onPacketReceived(const uint8_t *buffer, size_t size);
