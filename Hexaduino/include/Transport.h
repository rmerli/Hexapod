#include <Arduino.h>
struct Message
{
    int forward;
    int sideway;
    int direction;
    int tilt_x;
    int tilt_y;
    int gait; 
};


void onPacketReceived(const uint8_t *buffer, size_t size);

String encodeMessage(Message msg);

Message decodeMessage(String raw_msg);
