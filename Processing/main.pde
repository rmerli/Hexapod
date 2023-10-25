class Point{
  float x;
  float y;
  Point(float x,float y) {
    this.x = x;
    this.y = y;
  }
  Point(){};
}

float c = 104.0;
float a = 209.0;
float scalar = 400;
int i = 100;
boolean dir = true;
color BlueColor = color(0, 80, 110);
int offset_x = 200;
int offset_y = 200;


float speed = 0.003;
float t = 0;
boolean flip = false;
float angleX = degToRad(50);
float angleY = degToRad(0);
float angleZ = degToRad(0);
float distance = 2;

Hexapod hexa;

float[][] rotationZ;
float[][] rotationX;
float[][] rotationY;

void setup() {
  size(1000, 1000);
  smooth();
  hexa = new Hexapod();
}


void draw() {
  
  rotationZ = new float[][]{                           
                            {cos(angleZ), -sin(angleZ), 0},
                            {sin(angleZ), cos(angleZ), 0},
                            {0, 0 , 1}, 
                          };
  
   rotationX = new float[][]{
                          {1, 0 , 0},
                          {0, cos(angleX), -sin(angleX)},
                          {0, sin(angleX), cos(angleX)},
                        };
                        
  rotationY = new float[][]{
                          {cos(angleY),0, -sin(angleY)},
                          {0, 1 , 0},  
                          {sin(angleY),0, cos(angleY)},
  
                        };                        
  
  background(0);
  translate(1000/2, 1000/2);
  renderHexapod(hexa);
  angleZ += 0.01;
  angleX += 0.01;
}


void renderHexapod(Hexapod hexa){
  stroke(255);
  strokeWeight(8);
  
  for (PVector p : hexa.body) {
    PVector rotated = mulMatrixVector(rotationZ, p);
    rotated = mulMatrixVector(rotationX, rotated);
    rotated = mulMatrixVector(rotationY, rotated);
    float z = 1 / (distance - rotated.z);
    float[][] projection = {
      {z,0,0},
      {0,z,0},
    };
    
    PVector projected = mulMatrixVector(projection, rotated);
    projected.mult(scalar);
    point(projected.x, projected.y);
  }
  
  strokeWeight(2);
  
  for (int i = 0 ; i <= 4; i++){
    PVector rotatedFrom = mulMatrixVector(rotationZ, hexa.body[i % 4]);
    rotatedFrom = mulMatrixVector(rotationX, rotatedFrom);
    rotatedFrom = mulMatrixVector(rotationY, rotatedFrom);
    float z = 1 / (distance - rotatedFrom.z);
    float[][] projection = {
      {z,0,0},
      {0,z,0},
    };
    PVector projectedFrom = mulMatrixVector(projection, rotatedFrom);
    projectedFrom.mult(scalar);
    
    PVector rotatedTo = mulMatrixVector(rotationZ, hexa.body[(i+1) % 4]);
    rotatedTo = mulMatrixVector(rotationX, rotatedTo);
    rotatedTo = mulMatrixVector(rotationY, rotatedTo); 
    z = 1 / (distance - rotatedTo.z);
    projection = new float[][]{
      {z,0,0},
      {0,z,0},
    };
    
    PVector projectedTo = mulMatrixVector(projection, rotatedTo);
    projectedTo.mult(scalar);
    line(projectedFrom.x, projectedFrom.y, projectedTo.x, projectedTo.y);
  }
  
  for (int leg = 0; leg < 6 ; leg++) {
    PVector rotated1 = mulMatrixVector(rotationZ, hexa.legs[leg][0]);
    PVector rotated2 = mulMatrixVector(rotationZ, hexa.legs[leg][1]);
    PVector rotated3 = mulMatrixVector(rotationZ, hexa.legs[leg][2]);
    
    rotated1 = mulMatrixVector(rotationX, rotated1);
    rotated2 = mulMatrixVector(rotationX, rotated2);
    rotated3 = mulMatrixVector(rotationX, rotated3);
    
    rotated1 = mulMatrixVector(rotationY, rotated1);
    rotated2 = mulMatrixVector(rotationY, rotated2);
    rotated3 = mulMatrixVector(rotationY, rotated3);
    
    float z1 = 1 / (distance - rotated1.z);
    float z2 = 1 / (distance - rotated2.z);
    float z3 = 1 / (distance - rotated3.z);
    float[][] projection1 = {
      {z1,0,0},
      {0,z1,0},
    };
    
    float[][] projection2 = {
      {z2,0,0},
      {0,z2,0},
    }; 
    
    float[][] projection3 = {
      {z3,0,0},
      {0,z3,0},
    };
    
    PVector projected1 = mulMatrixVector(projection1, rotated1);
    PVector projected2 = mulMatrixVector(projection2, rotated2);
    PVector projected3 = mulMatrixVector(projection3, rotated3);
    
    projected1.mult(scalar);
    projected2.mult(scalar);
    projected3.mult(scalar);
    
    strokeWeight(8);
    point(projected1.x, projected1.y);
    point(projected2.x, projected2.y);
    point(projected3.x, projected3.y);
    
    strokeWeight(2);
    
    line(projected1.x, projected1.y, projected2.x, projected2.y);
    line(projected2.x, projected2.y, projected3.x, projected3.y);
  }

}


void drawLines(float j1, float  j2) {

  float femore_l = c;
  float tibia_l = a;

  float tibia_angle = j2 + j1;

  float x2 = femore_l * cos(j1);
  float y2 = femore_l * sin(j1);

  float x3 = tibia_l * cos(tibia_angle);
  float y3 = tibia_l * sin(tibia_angle);

  x3 = x2 + x3;
  y3 = y2 + y3;


  strokeWeight(16);
  stroke(150, 150, 150);

  line(0, 0, x2, y2);
  line(x2, y2, x3, y3);

  stroke(255, 0, 0);
  point(0, 0);
  stroke(0, 0, 0);
  point(x2, y2);
  point(x3, y3);
}

float[] updateAngles(float x, float y) {
  //println(x, y);
  float b =  sqrt(pow(x, 2) + pow(y, 2));
  float phi1 = acos(( pow(b, 2) + pow(c, 2) - pow(a, 2) ) / (2*b*c));
  float phi2 = acos(( pow(a, 2) + pow(c, 2) - pow(b, 2) ) / (2*a*c));
  float phi3 = atan(y/x);

  float[] angles = new float[2];

  angles[0] = (phi3 - phi1);
  angles[1] =  (PI - phi2);

  if ((angles[0] * (180/PI)) > 90) {
    angles[0] = 90 * (PI/180);
  }

  if ((angles[0] * (180/PI)) < -90) {
    angles[0] = -90 * (PI/180);
  }

  if ((angles[1] * (180/PI)) > 165) {
    angles[1] = 165 * (PI/180);
  }
  return angles;
}

float degToRad(float angle) {
  return angle * (PI/180);
}

float radToDeg(float angle) {
  return angle * (180/PI);
}
