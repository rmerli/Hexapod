float scalar = 400;

float angleX = degToRad(0);
float angleY = degToRad(0);
float angleZ = degToRad(0);

float[][] worldMatrix;

float distance = 2;

void renderHexapod(Hexapod hexa){
  worldMatrix = matmul(makeRotationXMatrix(angleX), makeRotationYMatrix(angleY));
  worldMatrix = matmul(worldMatrix, makeRotationZMatrix(angleZ));
  stroke(255);
  strokeWeight(8);
  
  for (PVector p : hexa.body) {
    PVector transformed = mulMatrixVector(worldMatrix, p);
    float z = 1 / (distance - transformed.z);
    float[][] projection = {
      {z,0,0},
      {0,z,0},
    };
    
    PVector projected = mulMatrixVector(projection, transformed);
    projected.mult(scalar);
    point(projected.x, projected.y);
  }
  
  strokeWeight(2);
  for (int i = 0 ; i <= 4; i++){
    PVector transformedFrom = mulMatrixVector(worldMatrix, hexa.body[i % 4]);
    float z = 1 / (distance - transformedFrom.z);
    float[][] projection = {
      {z,0,0},
      {0,z,0},
    };
    PVector projectedFrom = mulMatrixVector(projection, transformedFrom);
    projectedFrom.mult(scalar);
    
    PVector transformedTo = mulMatrixVector(worldMatrix, hexa.body[(i+1) % 4]);
     
    z = 1 / (distance - transformedTo.z);
    projection = new float[][]{
      {z,0,0},
      {0,z,0},
    };
    
    PVector projectedTo = mulMatrixVector(projection, transformedTo);
    projectedTo.mult(scalar);
    line(projectedFrom.x, projectedFrom.y, projectedTo.x, projectedTo.y);
  }
  
  for (int leg = 0; leg < 6 ; leg++) {
    PVector transformed1 = mulMatrixVector(worldMatrix, hexa.legs[leg][0]);
    PVector transformed2 = mulMatrixVector(worldMatrix, hexa.legs[leg][1]);
    PVector transformed3 = mulMatrixVector(worldMatrix, hexa.legs[leg][2]);
    
    float z1 = 1 / (distance - transformed1.z);
    float z2 = 1 / (distance - transformed2.z);
    float z3 = 1 / (distance - transformed3.z);
    
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
    
    PVector projected1 = mulMatrixVector(projection1, transformed1);
    PVector projected2 = mulMatrixVector(projection2, transformed2);
    PVector projected3 = mulMatrixVector(projection3, transformed3);
    
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
