#include <Vector.h>
float lerp(float a, float b, float f)
{
    return a * (1.0 - f) + (b * f);
};

Vector2 lerp(Vector2 a, Vector2 b, float f)
{
    return Vector2(lerp(a.x, b.x, f), lerp(a.y, b.y, f));
};

Vector3 lerp(Vector3 a, Vector3 b, float f)
{
    return Vector3(lerp(a.x, b.x, f), lerp(a.y, b.y, f), lerp(a.z, b.z, f));
};

int binomialCoefficient(int n, int k)
{
  int result = 1;

  // Calculate the binomial coefficient using the formula:
  // (n!) / (k! * (n - k)!)
  for (int i = 1; i <= k; i++)
  {
    result *= (n - (k - i));
    result /= i;
  }

  return result;
}

Vector3 GetPointOnBezierCurve(Vector3 *points, int numPoints, float t)
{
  Vector3 pos;

  for (int i = 0; i < numPoints; i++)
  {
    float b = binomialCoefficient(numPoints - 1, i) * pow(1 - t, numPoints - 1 - i) * pow(t, i);
    pos.x += b * points[i].x;
    pos.y += b * points[i].y;
    pos.z += b * points[i].z;
  }

  return pos;
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

Vector3 mulMatrixVector(float matrix[3][3], Vector3 point)
{
    float result[3] = {0, 0, 0};
    float floatPoint[3] = {point.x, point.y, point.z};

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            result[row] += matrix[row][col] * floatPoint[col];
        }
    }

    return Vector3(result[0], result[1], result[2]);
}

void makeRotationZMatrix(float angle, float matrix[3][3]) 
{
    matrix[0][0] = cos(angle);
    matrix[0][1] = -sin(angle);
    matrix[0][2] = 0;
    matrix[1][0] = sin(angle);
    matrix[1][1] = cos(angle);
    matrix[1][2] = 0;
    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;
}

float degToRad(float angle) {
  return angle * (PI/180);
}

float radToDeg(float angle) {
    return angle * (180/PI);
}

Vector3 rotatePoint(Vector3 point, float angle){
    float rotationMatrix[3][3];
    makeRotationZMatrix(degToRad(angle), rotationMatrix);
    return mulMatrixVector(rotationMatrix, point);
}
