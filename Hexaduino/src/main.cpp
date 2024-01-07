#include <Arduino.h>
#include <vector.h>
#include <hexapod.h>

#define servo_max 2350
#define servo_min 400

Hexapod *hexapod;


int lastExec = 0;
int started = 0;

Vector2 command = {0,0};

void setup()
{
  Serial2.begin(115200);
  hexapod = new Hexapod();
  started = millis();
  delay(1000);
  hexapod->walk();
}

void loop()
{

  hexapod->carCommand.y = -50;

  if (( millis() - started) > 5000) {
    started = millis();
  }
  hexapod->update();
}
