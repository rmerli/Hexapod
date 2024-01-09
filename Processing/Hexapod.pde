class Stance{
  Leg[] legs = new Leg[6];
  Stance() {
    for (int i = 0; i < legs.length; i++) {
      legs[i] = new Leg();
    }
  }
}

class Leg{
  PVector position = new PVector(100.0, 0, -50);  
  PVector startPoint = new PVector(100.0, 25.0, -50.0);
  PVector[] controlPoint;
  boolean firstCycle = true;
  float progress;
  LegStatus status;

  Leg() {
    this.position = new PVector(100.0, 0, -50);
    this.controlPoint = new PVector[]{new PVector(100.0, 0, -50)};
    this.progress = 0.0;
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
  
  Status status = Status.STANDING;
  Status prevStatus = Status.STANDING;
   
  float cycleDuration = 10000;
  float speed = 50;
  float direction = 1;
  float maxSpeed = 200;

  PVector carCommand = new PVector(0,0,0);

  float femore_l = 75/divider;
  float tibia_l = 150/divider;
  
  float body_wide = 100/divider;
  float body_long = 100/divider;
  
  Gait gait = Gait.TRI;

  PVector standPos = new PVector(100.0, 0, -50);
  PVector startPos = new PVector(100.0, 25.0, -50.0);
  PVector midPos = new PVector(100.0, 0.0, -25.0);
  PVector target = new PVector(100.0, -25.0, -50.0);


  PVector[] lifting = {this.startPos, this.midPos, this.target};
  PVector[] starting = {this.standPos, new PVector(this.standPos.x, (this.target.y - this.standPos.y)/2, this.midPos.z), this.target};
  PVector[] startingPushing = {this.standPos, new PVector(this.standPos.x,(this.startPos.y - this.standPos.y)/2,this.standPos.z), this.startPos};

  PVector[] pushing = {this.target, this.standPos, this.startPos};

  float progressBreakpoint = 0.5;  
  
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
    if (leg == 0 || leg == 3) {
      j1 -= 45;
    }
    
    if (leg == 2 || leg == 5) {
      j1 += 45;
    }
    
    if (leg > 2){
      j1 = 360 - j1;
      j2 = 180 - j2;
      j3 = (360 - j3) * 1;
    }
     PVector[] newPos = forwardKinematicsLeg(j1, j2, j3, this.legs[leg][0]);
     this.legs[leg][1] = newPos[0];
     this.legs[leg][2] = newPos[1];
  }


  public void command() {
    
  }

  // public void walk() {
  //   if (this.status != Status.STANDING) {
  //     return;
  //   }
  //
  //   this.status = Status.WALKING;
  //    
  //    if (this.status == Status.WALKING && this.prevStatus != this.status) {
  //     switch (this.gait) {
  //       case TRI :
  //         this.stance.legs[0].progress = 0;
  //         this.stance.legs[1].progress = 0.5;
  //         this.stance.legs[2].progress = 0;
  //         this.stance.legs[3].progress = 0.5;
  //         this.stance.legs[4].progress = 0;
  //         this.stance.legs[5].progress = 0.5;
  //
  //         this.progressBreakpoint = 0.5;    
  //         println("resetting progresses");
  //         break;
  //       case WAVE :
  //         this.stance.legs[0].progress = 0;
  //         this.stance.legs[1].progress = (1/6.0) * 5;
  //         this.stance.legs[2].progress = (1/6.0) * 4;
  //         this.stance.legs[3].progress = (1/6.0);
  //         this.stance.legs[4].progress = (1/6.0) * 2;
  //         this.stance.legs[5].progress = (1/6.0) * 3;
  //
  //         this.progressBreakpoint = 1.0/6.0; 
  //         break;
  //     }
  //
  //     for(int l = 0; l < this.stance.legs.length; l++) {
  //       float t = this.stance.legs[l].progress; 
  //       this.stance.legs[l].firstCycle = true;
  //       if (t >= progressBreakpoint) {
  //         //pushing
  //         this.stance.legs[l].controlPoint = startingPushing;
  //       }else {
  //         //lifting
  //         this.stance.legs[l].controlPoint = starting;
  //       }
  //     }
  //     
  //     this.prevStatus = this.status;
  //   }
  // }


  public void walk()
  {
    if (this.status != Status.STANDING){
        return;
    }
    print("walking");
    this.status = Status.WALKING;
    this.initGait();
  }

  private void initGait()
  {
    if (this.status == Status.WALKING && this.prevStatus != this.status) {
        switch (this.gait) {
            case TRI :
                this.stance.legs[0].progress = 0;
                this.stance.legs[1].progress = (this.cycleDuration/2) / this.cycleDuration;
                this.stance.legs[2].progress = 0;
                this.stance.legs[3].progress = (this.cycleDuration/2) / this.cycleDuration;
                this.stance.legs[4].progress = 0;
                this.stance.legs[5].progress = (this.cycleDuration/2) / this.cycleDuration;

                this.progressBreakpoint = (this.cycleDuration/2) / this.cycleDuration;    

                break;
            case WAVE :
                this.stance.legs[0].progress = 0;
                this.stance.legs[1].progress = ((this.cycleDuration/6.0) * 5) / this.cycleDuration;
                this.stance.legs[2].progress = ((this.cycleDuration/6.0) * 4) / this.cycleDuration;
                this.stance.legs[3].progress = ((this.cycleDuration/6.0)) / this.cycleDuration;
                this.stance.legs[4].progress = ((this.cycleDuration/6.0) * 2 ) / this.cycleDuration;
                this.stance.legs[5].progress = ((this.cycleDuration/6.0) * 3 ) / this.cycleDuration;

                this.progressBreakpoint = (this.cycleDuration/6.0) / this.cycleDuration;
                break;
        }
        this.prevStatus = this.status;
    }
  }

  public void stop() {
    if (this.status == Status.WALKING) {
      this.status = Status.STOPPING;
    }

    // needs to stop
    if (this.status == Status.STOPPING && this.status != this.prevStatus) {
      for(int l = 0; l < this.stance.legs.length; l++) {
        float t = this.stance.legs[l].progress;
        
        if (t >= progressBreakpoint) {
          //on the ground, needs to go to the stand position in a line
          this.stance.legs[l].controlPoint = new PVector[]{this.stance.legs[l].position, this.standPos};
          this.stance.legs[l].progress = 0.5;
        }else {
          //on the air, needs to arc back to the stand position
          this.stance.legs[l].controlPoint = new PVector[]{this.stance.legs[l].position, this.standPos};
          this.stance.legs[l].progress = 0.5;
        }
      }
      this.prevStatus = Status.STOPPING;
    }
  }

  // private void updateStance() {
  //   if (this.status == Status.STANDING) {
  //     return;
  //   }
  //
  //   for(int l = 0; l < this.stance.legs.length; l++) {
  //     
  //     float t = this.stance.legs[l].progress;
  //
  //     if (t >= progressBreakpoint) {
  //       //pushing
  //       
  //       if (!this.stance.legs[l].firstCycle && this.status != Status.STOPPING) {
  //          this.stance.legs[l].controlPoint = pushing; 
  //       }
  //    
  //       this.stance.legs[l].position = getPointOnBezierCurve(this.stance.legs[l].controlPoint, this.stance.legs[l].controlPoint.length, map(t, this.progressBreakpoint, 1, 0,1));
  //     
  //     }else {
  //       //lifting
  //       this.stance.legs[l].position = getPointOnBezierCurve(this.stance.legs[l].controlPoint, this.stance.legs[l].controlPoint.length, map(t,0, this.progressBreakpoint, 0,1));
  //     }
  //
  //     if ((t < progressBreakpoint && t >= progressBreakpoint - 0.008) && (this.stance.legs[l].firstCycle)) {
  //       this.stance.legs[l].controlPoint = pushing;
  //       this.stance.legs[l].firstCycle = false;
  //     }
  //     
  //     if (this.stance.legs[l].progress < 1) {
  //       this.stance.legs[l].progress += 0.008;
  //     }
  //   }
  // }
  
  // private void checkProgress(){
  //   if (this.status == Status.STOPPING) {
  //     for(int l=0; l < this.stance.legs.length; l++) {
  //       if (this.stance.legs[l].progress < 1) {
  //         return;
  //       }
  //     }
  //     this.status = Status.STANDING;
  //     this.prevStatus = Status.STANDING;
  //     return;
  //   }
  //
  //   for(int l=0; l < this.stance.legs.length; l++) {
  //     if (this.stance.legs[l].progress > 1 && this.status == Status.WALKING) {
  //         this.stance.legs[l].progress = 0;
  //         this.stance.legs[l].firstCycle = false;
  //         this.stance.legs[l].controlPoint = lifting;
  //     }
  //   }
  // }


  

  private void updateSpeed()
  {
    if (this.carCommand.y >= 0) this.direction = 1;
    else this.direction = -1;

    this.speed = max(abs(carCommand.y), abs(carCommand.x));    
    if( this.speed > this.maxSpeed) {
        this.speed = this.maxSpeed;
    }
  }

  private void updateProgress()
  { 
    float currentProgress;
    for (int l = 0; l < 6; l++){
        //0.1 * 1000 = 100
      currentProgress = this.stance.legs[l].progress * this.cycleDuration;
      currentProgress += this.speed;
       
      this.stance.legs[l].progress = currentProgress / this.cycleDuration;
    
      if (this.stance.legs[l].progress > 1 && this.status == Status.WALKING) {
        this.stance.legs[l].progress = 0;
      }
    }
  } 

  private void planLegsPath()
  {
    if (status == Status.STANDING) {
        return;
    }

    for (int l = 0; l < 6; l++) {
        float t = this.stance.legs[l].progress;
        // to extract and make it a setting
        float stride = 25;
        float rotateStride = 10;
        float distance_from_ground = -50;
        float lift = 50;

        PVector straightControlPoints[] = new PVector[3];
        PVector steeringControlPoints[] = new PVector[3];
        PVector straightPoint;
        PVector steeringPoint;
        float weightSum = abs(this.carCommand.x) + abs(this.carCommand.y);
        /* println("sum = " + weightSum," x = " + this.carCommand.x," y = " + this.carCommand.y); */ 

        if (t >= this.progressBreakpoint) {
            //second half of the cycle aka LegStatus.PUSHING
            if (this.stance.legs[l].status != LegStatus.PUSHING) {
              this.stance.legs[l].startPoint = this.stance.legs[l].position;
            }
            this.stance.legs[l].status = LegStatus.PUSHING;

            straightControlPoints[0] = this.stance.legs[l].startPoint;
            straightControlPoints[1] = this.stance.legs[l].startPoint;
            straightControlPoints[2] = new PVector(this.stance.legs[l].startPoint.x, -this.direction * stride, distance_from_ground);

            straightPoint = getPointOnBezierCurve(straightControlPoints, 3, mapFloat(t, this.progressBreakpoint, 1, 0, 1));
            this.stance.legs[l].position = straightPoint;

            steeringControlPoints[0] = this.stance.legs[l].startPoint;
            steeringControlPoints[1] = new PVector(this.stance.legs[l].startPoint.x + 50, 0, distance_from_ground);
            steeringControlPoints[2] = new PVector(this.stance.legs[l].startPoint.x, rotateStride, distance_from_ground);

            steeringPoint = getPointOnBezierCurve(steeringControlPoints, 3, mapFloat(t, this.progressBreakpoint, 1, 0, 1));

            this.stance.legs[l].position = (straightPoint.mult(abs(this.carCommand.y)).add(steeringPoint.mult(abs(this.carCommand.x))).div(weightSum));

        }else{
            //fist half of the cycle aka LegStatus.LIFTING
            if (this.stance.legs[l].status != LegStatus.LIFTING) {
              this.stance.legs[l].startPoint = this.stance.legs[l].position;
            }
            this.stance.legs[l].status = LegStatus.LIFTING;

            straightControlPoints[0]= this.stance.legs[l].startPoint;
            straightControlPoints[1]= new PVector
                (
                    this.stance.legs[l].startPoint.x,
                    ((this.direction * stride) - this.stance.legs[l].startPoint.y)/2,
                    distance_from_ground + lift
                ); 
            straightControlPoints[2] = new PVector(this.stance.legs[l].startPoint.x, direction * stride, distance_from_ground);

            straightPoint = getPointOnBezierCurve(straightControlPoints, 3, mapFloat(t,0,this.progressBreakpoint, 0, 1));
            this.stance.legs[l].position = straightPoint;

            steeringControlPoints[0]= this.stance.legs[l].startPoint;
            steeringControlPoints[1]= new PVector
                (
                    this.stance.legs[l].startPoint.x + 50,
                    0,
                    distance_from_ground + lift
                ); 
            steeringControlPoints[2] = new PVector(this.stance.legs[l].startPoint.x, -rotateStride, distance_from_ground);

            steeringPoint = getPointOnBezierCurve(steeringControlPoints, 3, mapFloat(t,0,this.progressBreakpoint, 0, 1));
            /* println(steeringPoint, t) */;

            this.stance.legs[l].position = (straightPoint.mult(abs(this.carCommand.y)).add(steeringPoint.mult(abs(this.carCommand.x))).div(weightSum));
        }
    }
  }

  private void updateLegsPosition()
  {
    PVector center = new PVector(100, 0.0, -25);
    
    for (int i = 0; i < stance.legs.length; i++) {
      
      PVector point = new PVector(this.stance.legs[i].position.x - center.x, this.stance.legs[i].position.y - center.y, this.stance.legs[i].position.z - center.z);
      
      float[] angles = IKleg(this.stance.legs[i].position.x, this.stance.legs[i].position.y, this.stance.legs[i].position.z);
      if (i == 0 || i == 3){
        point = mulMatrixVector(makeRotationZMatrix(degToRad(45)), point);
        point.x += center.x;
        point.y += center.y;
        point.z += center.z;
        angles = IKleg(point.x, point.y, point.z);
      }
      
      if (i == 2 || i == 5){
        point = mulMatrixVector(makeRotationZMatrix(degToRad(-45)), point);
        point.x += center.x;
        point.y += center.y;
        point.z += center.z;
        angles = IKleg(point.x, point.y, point.z);
      }
      this.setLegPositionByAngle(i,angles[0], angles[1], angles[2]);
      //this.setLegPositionByAngle(i,0,0,0);
    }
  }

  public void update() {
    this.updateSpeed();
    this.updateProgress();
    this.planLegsPath();
    this.updateLegsPosition();
    // this.checkProgress();
    // this.updateStance();
    // this.updateLegs();
  }  
}
