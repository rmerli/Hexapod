PVector[] forwardKinematicsLeg(float j1, float j2, float  j3, PVector offset) {

  float femore_l = hexa.femore_l;
  float tibia_l = hexa.tibia_l;  
  j3 = 180 - j3;
  
  j1 = degToRad(j1);
  j2 = degToRad(j2);
  j3 = degToRad(j3);
  
  float d3 = sin(j2) * femore_l;
  
  float the4 = degToRad(180) - (j2 + degToRad(90));
  
  float the5 = j3 - the4;
  
  float d6 = cos(the5) * tibia_l;
  
  float d4 = cos(j2) * femore_l;
  
  float d5 = sin(the5) * tibia_l;
  
  float d1 = d4 + d5;
  
  PVector femore = new PVector();
  PVector tibia = new PVector();
 
  femore.x = (cos(j1) * d4);
  femore.y = (sin(j1) * d4); 
  femore.z = d3;
  
  tibia.x = cos(j1) * d1;
  tibia.y = sin(j1) * d1;
  tibia.z = d3 - d6;
  
  PVector[] result = new PVector[2];
  
  result[0] = femore.add(offset);
  result[1] = tibia.add(offset);
  return result; 
}

float[] IKleg(float x, float y, float z) {

  float femore_length = hexa.femore_l * hexa.divider;
  float tibia_length = hexa.tibia_l * hexa.divider;  
  
  
  
  float r1 = sqrt(pow(x, 2) + pow(y, 2));
  float r2 = z;
  float r3 = sqrt(pow(r1, 2) + pow(r2, 2));

  float phi1 = acos((pow(r3, 2) + pow(femore_length, 2) - pow(tibia_length, 2)) / (2 * r3 * femore_length));
  float phi2 = acos((pow(tibia_length, 2) + pow(femore_length, 2) - pow(r3, 2)) / (2 * tibia_length * femore_length));
  float phi3 = atan(r2 / r1);

  float[] result = new float[3];

  result[0] = atan(y / x) * (180 / PI);
  result[1] = (phi3 + phi1) * (180 / PI);
  result[2] = (PI - phi2) * (180 / PI);
  
  //println(result[0]);
  //println(result[1]);
  //println(result[2]);
  
  return result;
}


float degToRad(float angle) {
  return angle * (PI/180);
}

float radToDeg(float angle) {
  return angle * (180/PI);
}
