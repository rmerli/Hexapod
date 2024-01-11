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


String encodeMessage(Message msg);

Message decodeMessage(String raw_msg);
