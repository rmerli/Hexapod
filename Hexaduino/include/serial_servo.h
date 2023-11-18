#include <Arduino.h>
#ifndef serial_servo_defined
#define serial_servo_defined
class SerialServo
{
public:
    SerialServo(HardwareSerial *serial, int id);
    void write(float angle);
    void setSpeed(int speed);
    void setMin(int min);
    void setMax(int max);

private:
    HardwareSerial *serial;
    int id;
    int min;
    int max;
    int speed;

    void bus_servo_control(int id, int value, int time);
    void bus_servo_set_id(uint8_t id);
    void bus_servo_read(uint8_t id);
    uint16_t bus_servo_get_value(void);
    void bus_servo_uart_recv(uint8_t Rx_Temp);
    int angleToCommand(float angle);
};
#endif