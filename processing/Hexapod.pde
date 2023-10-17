
void setup() {
    size(1000, 1000);
    smooth();

}
  
float c = 173.0;
float a = 155.0;
int i = 100;
boolean dir = true;
color BlueColor = color(0, 80, 110);
int offset_x = 200;
int offset_y = 200;
void draw() {  
    if (i >= 200 && dir) {
      dir = false;
    }
    
    if (i <= 100 && !dir) {
      dir = true;    
    }
    
    if (dir) {
      i++;
    }else {
      i--;
    }
    
    background(BlueColor);
    
    float[] angles = updateAngles(mouseX - offset_x, mouseY - offset_y);
    drawLines(angles[0], angles[1]);
    delay(10);
}

void drawLines(float j1, float  j2) {

  float femore_l = c;
  float tibia_l = a;
  
  float x2 = femore_l * cos(j1);
  float y2 = femore_l * sin(j1);
  
  float x3 = tibia_l * cos(j2 + j1);
  float y3 = tibia_l * sin(j2 + j1);
  
  x2 = offset_x + x2;
  y2 = offset_y + y2;
  
  x3 = x2 + x3;
  y3 = y2 + y3;
  
  
  strokeWeight(16);  
  stroke(150,150,150);
  line(offset_x,offset_y, x2, y2);
  line(x2, y2, x3, y3); 
  
  stroke(255,0,0);
  point(offset_x,offset_y);
  stroke(0,0,0);
  point(x2, y2);
  point(x3, y3);
}

float[] updateAngles(float x, float y) {
  println(x,y);
  float b =  sqrt(pow(x,2) + pow(y,2));
  float phi1 = acos(( pow(b,2) + pow(c,2) - pow(a,2) ) / (2*b*c));
  float phi2 = acos(( pow(a,2) + pow(c,2) - pow(b,2) ) / (2*a*c));
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
  
  if ((angles[1] * (180/PI)) > 90) {
    angles[1] = 90 * (PI/180);
  }
  return angles;
}
