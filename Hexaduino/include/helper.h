#include <vector.h>
#ifndef helper_defined
#define helper_defined
    float lerp(float a, float b, float f);
    Vector2 lerp(Vector2 a, Vector2 b, float f);
    Vector3 lerp(Vector3 a, Vector3 b, float f);
    int binomialCoefficient(int n, int k);
    Vector3 GetPointOnBezierCurve(Vector3 *points, int numPoints, float t);

    float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);

    Vector3 mulMatrixVector(float matrix[3][3], Vector3 point);

    void makeRotationZMatrix(float angle, float matrix[3][3]);

    float degToRad(float angle);

    float radToDeg(float angle);

    enum Gait { TRI, WAVE};
    enum Status { STANDING, STOPPING, WALKING};
    enum LegStatus { LIFTING, PUSHING };
#endif
