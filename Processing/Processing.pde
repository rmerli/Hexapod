
Hexapod hexa;

PVector standPos = new PVector(100.0, 0, -50);

PVector startPos = new PVector(100.0, 25.0, -50.0);


PVector midPos = new PVector(100.0, 0.0, -25.0);
PVector target = new PVector(100.0, -25.0, -50.0);


PVector[] lifting = {startPos, midPos, target};

PVector[] starting = {standPos, new PVector(standPos.x, target.y, midPos.z), target};
PVector[] startingPushing = {standPos, startPos, startPos};

PVector[] pushing = {target, standPos, startPos};

float progressBreakpoint = 0.5;

void setup() {
  size(1000, 1000);
  smooth();
  hexa = new Hexapod();
  renderUI();
}

boolean isLifting = true;


PVector[] legs = lifting;

float t = 0;


enum Status {
  STANDING,
  WALKING
}

Status status = Status.STANDING;

void draw() {
  for(int l=0; l < hexa.stance.legs.length; l++) {
    if (hexa.stance.legs[l].progress > 1) {
        hexa.stance.legs[l].progress = 0;
    }
  }
  
  
  
  pushMatrix();
  translate(width/2, height/2);
  background(0);             
  
  
  hexa.update();
  renderHexapod(hexa);
  
  PVector[] liftingControlPoints = lifting;
  PVector[] pushingControlPoints = pushing;
  // liftingPoint = getPointOnBezierCurve(lifting, 3, t);
  // pushingPoint = getPointOnBezierCurve(pushing, 3, t);

  if (status == Status.STANDING) {

    hexa.stance.legs[0].progress = 0;
    hexa.stance.legs[1].progress = (1/6.0) * 5;
    hexa.stance.legs[2].progress = (1/6.0) * 4;
    hexa.stance.legs[3].progress = (1/6.0);
    hexa.stance.legs[4].progress = (1/6.0) * 2;
    hexa.stance.legs[5].progress = (1/6.0) * 3;

    // hexa.stance.legs[0].progress = 0;
    // hexa.stance.legs[1].progress = 0.5;
    // hexa.stance.legs[2].progress = 0;
    // hexa.stance.legs[3].progress = 0.5;
    // hexa.stance.legs[4].progress = 0;
    // hexa.stance.legs[5].progress = 0.5;

    // progressBreakpoint = 0.5;
    progressBreakpoint = 1.0/6.0;

    // for(int l = 0; l < hexa.stance.legs.length; l++) {
    //   if (l % 2 == 0){
    //     hexa.stance.legs[l].progress = 0.5;
    //   }
    // }
    
    liftingControlPoints = starting;
    pushingControlPoints = startingPushing;

    //  liftingPoint = getPointOnBezierCurve(starting, 3, t);
    //  pushingPoint = getPointOnBezierCurve(startingPushing, 3, t);
  }
  
  
  for(int l=0; l < hexa.stance.legs.length; l++) {
    
    float t = hexa.stance.legs[l].progress;

    if (t > progressBreakpoint) {
      //pushing
      hexa.stance.legs[l].position = getPointOnBezierCurve(pushingControlPoints, 3, map(t, progressBreakpoint, 1, 0,1));
    }else {
      //lifting
      hexa.stance.legs[l].position = getPointOnBezierCurve(liftingControlPoints, 3, map(t,0, progressBreakpoint, 0,1));
    }

    hexa.stance.legs[l].progress += 0.008;
  }

  popMatrix();
  
  status = Status.WALKING;
}


int binomialCoefficient(int n, int k)
{
  int result = 1;

  for (int i = 1; i <= k; i++)
  {
    result *= (n - (k - i));
    result /= i;
  }

  return result;
}

PVector getPointOnBezierCurve(PVector[] points, int numPoints, float t)
{
  PVector pos = new PVector();

  for (int i = 0; i < numPoints; i++)
  {
    float b = binomialCoefficient(numPoints - 1, i) * pow(1 - t, numPoints - 1 - i) * pow(t, i);
    pos.x += b * points[i].x;
    pos.y += b * points[i].y;
    pos.z += b * points[i].z;
  }

  return pos;
}
