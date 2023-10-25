class Hexapod{
  PVector[] body = new PVector[4];
  PVector[][] legs = {
    new PVector[3],
    new PVector[3],
    new PVector[3],
    new PVector[3],
    new PVector[3],
    new PVector[3]
  };
  
  float divider = 400;
  
  float femore_l = 75/divider;
  float tibia_l = 150/divider;
  
  float body_wide = 200/divider;
  float body_long = 220/divider;
  
  Hexapod() {
    body[0] = new PVector(-body_wide/2, -(body_long/2), 0);
    body[1] = new PVector(body_wide/2, -(body_long/2), 0);
    body[2] = new PVector(body_wide/2, (body_long/2), 0);
    body[3] = new PVector(-body_wide/2, (body_long/2), 0);
    
    legs[0][0] = new PVector(body_wide/2,-(body_long/2),0);
    legs[0][1] = new PVector(body_wide/2 + femore_l,-(body_long/2),50/divider);
    legs[0][2] = new PVector(body_wide/2 + femore_l + tibia_l,-(body_long/2),-100/divider);
    
    legs[1][0] = new PVector(body_wide/2,0,0);
    legs[1][1] = new PVector(body_wide/2 + femore_l,0,50/divider);
    legs[1][2] = new PVector(body_wide/2 + femore_l + tibia_l,0,-100/divider);
    
    legs[2][0] = new PVector(body_wide/2,(body_long/2),0);
    legs[2][1] = new PVector(body_wide/2 + femore_l,(body_long/2),50/divider);
    legs[2][2] = new PVector(body_wide/2 + femore_l + tibia_l,(body_long/2),-100/divider);
    
    legs[3][0] = new PVector(-body_wide/2,-(body_long/2),0);
    legs[3][1] = new PVector(-body_wide/2 - femore_l,-(body_long/2),50/divider);
    legs[3][2] = new PVector(-body_wide/2 - femore_l - tibia_l,-(body_long/2),-100/divider);
    
    legs[4][0] = new PVector(-body_wide/2,0,0);
    legs[4][1] = new PVector(-body_wide/2 - femore_l,0,50/divider);
    legs[4][2] = new PVector(-body_wide/2 - femore_l - tibia_l,0,-100/divider);
    
    legs[5][0] = new PVector(-body_wide/2,(body_long/2),0);
    legs[5][1] = new PVector(-body_wide/2 - femore_l,(body_long/2),50/divider);
    legs[5][2] = new PVector(-body_wide/2 - femore_l - tibia_l,(body_long/2),-100/divider);
  }
  
  void copy(Hexapod hexa) {
    
    for (int i = 0; i < hexa.body.length; i++) {
      body[i] = new PVector(hexa.body[i].x, hexa.body[i].y, hexa.body[i].z);  
    }
    
    for (int leg = 0; leg < hexa.legs.length; leg++) {
      for (int p = 0; p < hexa.legs[leg].length; p++) {
        legs[leg][p] = new PVector(hexa.legs[leg][p].x,hexa.legs[leg][p].y,hexa.legs[leg][p].z);
      }
    }
  }
}
