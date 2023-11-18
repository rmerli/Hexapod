class Stance{
  PVector[] legs = new PVector[6];
  Stance() {
    for (int i = 0; i < legs.length; i++) {
      legs[i] = new PVector(150, 0, -50);
    }
  }
}

class Hexapod{
  PVector[] body = new PVector[4];
  Stance stance = new Stance();
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
  
  float body_wide = 100/divider;
  float body_long = 100/divider;
  
  
  
  Hexapod() {
    this.body[0] = new PVector(-this.body_wide/2, -(this.body_long/2), 0);
    this.body[1] = new PVector(this.body_wide/2, -(this.body_long/2), 0);
    this.body[2] = new PVector(this.body_wide/2, (this.body_long/2), 0);
    this.body[3] = new PVector(-this.body_wide/2, (this.body_long/2), 0);
    
    this.legs[0][0] = new PVector(this.body_wide/2,-(this.body_long/2),0);
    this.legs[0][1] = new PVector(this.body_wide/2 + this.femore_l,-(this.body_long/2),0);
    this.legs[0][2] = new PVector(this.body_wide/2 + this.femore_l + tibia_l,-(this.body_long/2),0);
    
    this.legs[1][0] = new PVector(this.body_wide/2,0,0);
    this.legs[1][1] = new PVector(this.body_wide/2 + this.femore_l,0,0);
    this.legs[1][2] = new PVector(this.body_wide/2 + this.femore_l + this.tibia_l,0,0);
    
    this.legs[2][0] = new PVector(this.body_wide/2,(this.body_long/2),0);
    this.legs[2][1] = new PVector(this.body_wide/2 + this.femore_l,(this.body_long/2),0);
    this.legs[2][2] = new PVector(this.body_wide/2 + this.femore_l + this.tibia_l,(this.body_long/2),0);
    
    this.legs[3][0] = new PVector(-this.body_wide/2,-(this.body_long/2),0);
    this.legs[3][1] = new PVector(-this.body_wide/2 - this.femore_l,-(this.body_long/2),0);
    this.legs[3][2] = new PVector(-this.body_wide/2 - this.femore_l - this.tibia_l,-(this.body_long/2),0);
    
    this.legs[4][0] = new PVector(-this.body_wide/2,0,0);
    this.legs[4][1] = new PVector(-this.body_wide/2 - this.femore_l,0,0);
    this.legs[4][2] = new PVector(-this.body_wide/2 - this.femore_l - this.tibia_l,0,0);
    
    this.legs[5][0] = new PVector(-this.body_wide/2,(this.body_long/2),0);
    this.legs[5][1] = new PVector(-this.body_wide/2 - this.femore_l,(this.body_long/2),0);
    this.legs[5][2] = new PVector(-this.body_wide/2 - this.femore_l - this.tibia_l,(body_long/2),0);
  }
  
  void setLegPositionByAngle(int leg, float j1, float j2, float j3) {
    if (leg > 2){
      j1 = 360 - j1;
      j2 = 180 - j2;
      j3 = (360 - j3) * 1;
    }
     PVector[] newPos = forwardKinematicsLeg(j1, j2, j3, this.legs[leg][0]);
     this.legs[leg][1] = newPos[0];
     this.legs[leg][2] = newPos[1];
  }
  
  void update() {
    for (int i = 0; i < stance.legs.length; i++) {
      float[] angles =IKleg(this.stance.legs[i].x, this.stance.legs[i].y, this.stance.legs[i].z);
      this.setLegPositionByAngle(i,angles[0], angles[1], angles[2]);
    }
  }
}
