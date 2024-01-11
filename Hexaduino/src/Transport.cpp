#include <Transport.h>


Message decodeMessage(String rawMessage)
{
    Message decoded;
    size_t size = 6;
    int partials[size] = {0};

    int curr_index = 0;

    String leftover = rawMessage;

    for (int i = 0; i < size; i++)
    {
        curr_index = leftover.indexOf(';');
        partials[i] = leftover.substring(0, curr_index).toInt();
        leftover = leftover.substring(curr_index + 1);
    }

    decoded.forward = partials[0];
    decoded.sideway = partials[1];
    decoded.direction = partials[2];
    decoded.tilt_x = partials[3];
    decoded.tilt_y = partials[4];
    decoded.gait = partials[5];

    return decoded;
}

String encodeMessage(Message msg)
{
    return String(msg.forward) + ";" + String(msg.sideway) + ";" + String(msg.direction) + ";" + String(msg.tilt_x) + ";" + String(msg.tilt_y) + ";" + String(msg.gait);
}


