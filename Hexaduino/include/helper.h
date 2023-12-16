#include <vector.h>
#ifndef helper_defined
#define helper_defined
float lerp(float a, float b, float f);
Vector2 lerp(Vector2 a, Vector2 b, float f);
Vector3 lerp(Vector3 a, Vector3 b, float f);
int binomialCoefficient(int n, int k);
Vector3 GetPointOnBezierCurve(Vector3 *points, int numPoints, float t);
#endif