
Hexapod hexa;

PVector standPos = new PVector(100.0, 0, -50);

PVector startPos = new PVector(100.0, 25.0, -50.0);


PVector midPos = new PVector(100.0, 0.0, -25.0);
PVector target = new PVector(100.0, -25.0, -50.0);


PVector[] lifting = {startPos, midPos, target};

PVector[] starting = {standPos, new PVector(standPos.x, target.y, midPos.z), target};
PVector[] startingPushing = {standPos, startPos, startPos};

PVector[] pushing = {target, standPos, startPos};

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
  if (t > 1) {
      if(isLifting) {   
        isLifting = false;    
      }else{
        isLifting = true;
      }
    t = 0;  
  }
  
  
  pushMatrix();
  translate(width/2, height/2);
  background(0);             
  
  
  hexa.update();
  renderHexapod(hexa);
  
  
  PVector liftingPoint;
  liftingPoint = getPointOnBezierCurve(lifting, 3, t);
  PVector pushingPoint;
  pushingPoint = getPointOnBezierCurve(pushing, 3, t);
  
  
  if (status == Status.STANDING) {
     liftingPoint = getPointOnBezierCurve(starting, 3, t);
     pushingPoint = getPointOnBezierCurve(startingPushing, 3, t);
  }
  
  
  
  for(int l=0; l < hexa.stance.legs.length; l++) {
    if (l % 2 == 0){
      if (isLifting) {
        hexa.stance.legs[l] = liftingPoint;
      }else {
        hexa.stance.legs[l] = pushingPoint;
      }
    }else{
      if (!isLifting) {
        hexa.stance.legs[l] = liftingPoint;
      }else {
        hexa.stance.legs[l] = pushingPoint;
      }
    }
  }
  
  popMatrix();
  t += 0.008;
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
