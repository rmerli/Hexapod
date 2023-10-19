#include <Arduino.h>
#include <Servo.h>
#include <math.h>

// Servo pins
#define J1Pin 24
#define J2Pin 26
#define J3Pin 28

// Servos
Servo joint1;
Servo joint2;
Servo joint3;

void angleMove(float j1, float j2, float j3);
void cartesianMove(float x, float y, float z);
void cartesianMove3d(float x, float y, float z);

float c = 100.0;
float a = 200.0;

void setup() {
  Serial.begin(9600);
  
  // Servo instances
  joint1.attach(J1Pin);
  joint2.attach(J2Pin);
  joint3.attach(J3Pin);
  cartesianMove(250, 150, 0);
  Serial.println();
  cartesianMove3d(250, 0, 0);
  // angleMove(0,0,0);

}

void loop() {

  for (float i = -150; i <= 150; i = i + 10){
    cartesianMove(250, i, 0); 
    delay(15);
  }
 
  for (float i = 150; i >= -150; i = i - 10){
    cartesianMove(250, i, 0); 
    delay(15);
  } 

  // for (int i = -250; i >= -320; i = i - 2){
    //  cartesianMove(0,i);
  //   delay(10);
  // }
  
  
}

void cartesianMove3d(float x, float y, float z) {
  float a2 = c;
  float a3 = a;
  
  float j1 = atan(y/x) * (180/PI);
  float r1 = sqrt(pow(x,2) + pow(y,2));
  float r2 = z;
  
  float phi2 = atan(r2/r1);

  float r3 = sqrt(pow(r1,2) + pow(r2,2));


  float phi1 = acos((pow(a3,2) + pow(a2,2) - pow(r3,2))/(2*a2*a3));
  float phi3 = acos((pow(r3,2) + pow(a2,2) - pow(a3,2))/(2*a2*r3));

  float j2 = (phi1 + phi2) * (180/PI);
  float j3 = (PI - phi3) * (180/PI);
 
  Serial.println(j1);
  Serial.println(j2);
  Serial.println(j3);

  // angleMove(j1,j2,j3);
}

void cartesianMove(float x, float y, float z) {
  // Serial.println(x);
  // Serial.println(y);
  // Serial.println();

  // float r3 =  sqrt(pow(x,2) + pow(z,2));
  // float phi3 = acos(( pow(r3,2) + pow(c,2) - pow(a,2) ) / (2*r3*c));

  // float phi1 = acos(( pow(a,2) + pow(c,2) - pow(r3,2) ) / (2*a*c));

  // float phi2 = atan(z/y);
  
  // float j1 = atan(y/x) * (180/PI);
  // float j2 = (phi2 + phi1) * (180/PI);
  // float j3 =  (PI - phi3) * (180/PI);

  // Serial.println(j1);
  // Serial.println(j2);
  // Serial.println(j3);
  // angleMove(j1, j2, j3);

  float r1 = sqrt(pow(x,2) + pow(y,2));
  float r2 = z;
  float r3 = sqrt(pow(r1,2) + pow(r2,2));

  float phi1 = acos(( pow(r3,2) + pow(c,2) - pow(a,2) ) / (2*r3*c));
  float phi2 = acos(( pow(a,2) + pow(c,2) - pow(r3,2) ) / (2*a*c));
  float phi3 = atan(r2/r1); 

  float j1 = atan(y/x) * (180/PI);
  float j2 = (phi3 + phi1) * (180/PI);
  float j3 =  (PI - phi2) * (180/PI);
  Serial.println(j1);
  Serial.println(j2);
  Serial.println(j3);

  angleMove(j1, j2, j3);

 
  // angleMove(j1,j2);
}

void angleMove(float j1,float j2){
  joint2.write(j1 + 90);
  joint3.write(j2 + 90);
}

void angleMove(float j1,float j2, float j3){
  joint1.write(j1 + 90);
  joint2.write(j2 + 90);
  joint3.write(j3 + 50);
}
