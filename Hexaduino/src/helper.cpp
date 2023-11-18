#include <vector.h>
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
