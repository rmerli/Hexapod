#include <Servo.h>
#include <math.h>
#include <Ramp.h>


// Servo pins
#define J1Pin 24
#define J2Pin 52
#define J3Pin 28

// Servos
Servo joint1;
Servo joint2;
Servo joint3;


float c = 173.0;
float a = 155.0;

void setup() {
  Serial.begin(115200);
  
  // Servo instances
  joint1.attach(J1Pin);
  joint2.attach(J2Pin);
  joint3.attach(J3Pin);
  delay(1000);
}

void loop() {

  for (int i = -320; i <= -250; i = i + 2){
    cartesianMove(0,i);
    delay(10);
  }


  for (int i = -250; i >= -320; i = i - 2){
    cartesianMove(0,i);
    delay(10);
  }
  
  
}

void cartesianMove(float x, float y) {
  Serial.println(x);
  Serial.println(y);
  Serial.println();

  float b =  sqrt(pow(x,2) + pow(y,2));
  float phi1 = acos(( pow(b,2) + pow(c,2) - pow(a,2) ) / (2*b*c));
  float phi2 = acos(( pow(a,2) + pow(c,2) - pow(b,2) ) / (2*a*c));
  float phi3 = atan(y/x);
  
  float j1 = (phi3 + phi1) * (180/PI);
  float j2 =  (phi2 - PI) * (180/PI);
  
  angleMove(j1,j2);
}

void angleMove(float j1,float j2){
  joint2.write(j1 + 90);
  joint3.write(j2 + 90);
}
