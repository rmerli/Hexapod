PVector mulMatrixVector(float[][] matrix, PVector point) {
  float[] result = {0,0,0};
  float[] floatPoint = {point.x,point.y,point.z}; 
    for (int row = 0; row < matrix.length ; row++){
      for (int col = 0 ; col < matrix[row].length ; col++) {
        result[row] = result[row] + (matrix[row][col] * floatPoint[col]);
      }
    }
    
    return new PVector(result[0], result[1], result[2]);
}


//float[][] vecToMatrix(PVector v) {
//  float[][] m = new float[3][3];
//  for (int i = 0; i < 3; i++) {
//    m[i] = new float[1];
//  }
//  m[0][0] = v.x;
//  m[1][0] = v.y;
//  m[2][0] = v.z;
//  return m;
//}

//PVector matrixToVec(float [][]m) {
//  return new PVector(m[0][0], m[1][0], m.length > 2 ? m[2][0] : 0);
//}

////PVector mulMatrixVector(float[][] a, PVector vec) {
////  float[][] m = vecToMatrix(vec);
////  float[][] r = matmul(a, m);
////  return matrixToVec(r);
////}



//float[][] matmul(float[][] a, float[][] b) {
//  int colsA = a[0].length;
//  int rowsA = a.length;
//  int colsB = b[0].length;
//  int rowsB = b.length;

//  if (colsA != rowsB) {
//    println("Columns of A must match rows of B");
//    return null;
//  }

//  float[][] result = new float[rowsA][];
//  for (int j = 0; j < rowsA; j++) {
//    result[j] = new float[colsB];
//    for (int i = 0; i < colsB; i++) {
//      float sum = 0;
//      for (int n = 0; n < colsA; n++) {
//        sum += a[j][n] * b[n][i];
//      }
//      result[j][i] = sum;
//    }
//  }
//  return result;
//}
