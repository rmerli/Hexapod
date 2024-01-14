#include <Arduino.h>

#ifndef vector_defined
#define vector_defined
class Vector2
{
public:
    float x;
    float y;
    // constructor
    Vector2();

    Vector2(float newX, float newY);

    String toString();

    Vector2 operator+(Vector2 val);

    Vector2 operator*(float val);

    Vector2 operator*(Vector2 val);

    Vector2 rotate(int angle, Vector2 pivot);
};

class Vector3
{
public:
    float x;
    float y;
    float z;
    // constructor
    Vector3();

    Vector3(float newX, float newY, float newZ);

    bool operator!=(Vector3 val);

    bool operator==(Vector3 val);

    Vector3 operator*(float val);

    Vector3 operator*(Vector3 val);

    Vector3 operator/(Vector3 val);

    Vector3 operator/(float val);

    Vector3 operator+(Vector3 val);

    String toString();

    Vector3 rotate(int angle, Vector2 pivot);

    float distanceTo(Vector3 v);
};
#endif