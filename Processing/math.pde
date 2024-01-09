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
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
