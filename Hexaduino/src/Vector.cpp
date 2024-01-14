#include <Vector.h>

Vector2::Vector2()
{
    x = 0;
    y = 0;
};

Vector2::Vector2(float newX, float newY)
{
    x = newX;
    y = newY;
};

String Vector2::toString()
{
    String xs = String(x);
    String ys = String(y);

    String ret = "(" + xs + "," + ys + ")";
    return ret;
};

Vector2 Vector2::operator+(Vector2 val)
{
    // Implement the multiply operator
    Vector2 result;
    result.x = x + val.x;
    result.y = y + val.y;
    return result;
};

Vector2 Vector2::operator*(float val)
{
    // Implement the multiply operator
    Vector2 result;
    result.x = x * val;
    result.y = y * val;
    return result;
};

Vector2 Vector2::operator*(Vector2 val)
{
    // Implement the multiply operator
    Vector2 result;
    result.x = x * val.x;
    result.y = y * val.y;
    return result;
};

Vector2 Vector2::rotate(int angle, Vector2 pivot)
{

    // Translate line so pivot point is at the origin
    x -= pivot.x;
    y -= pivot.y;

    // Rotate point by angle
    int x_rotated = x * cos(angle) - y * sin(angle);
    int y_rotated = x * sin(angle) + y * cos(angle);

    // Translate point back to original position
    x = x_rotated + pivot.x;
    y = y_rotated + pivot.y;
    return Vector2(x, y);
};

Vector3::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
};

Vector3::Vector3(float newX, float newY, float newZ)
{
    x = newX;
    y = newY;
    z = newZ;
};

bool Vector3::operator!=(Vector3 val)
{
    return (x != val.x || y != val.y || z != val.z);
};

bool Vector3::operator==(Vector3 val)
{
    return (x == val.x && y == val.y && z == val.z);
};

Vector3 Vector3::operator*(float val)
{
    return Vector3(x * val, y * val, z * val);
};

Vector3 Vector3::operator*(Vector3 val)
{
    return Vector3(x * val.x, y * val.y, z * val.z);
};

Vector3 Vector3::operator/(Vector3 val)
{
    return Vector3(x / val.x, y / val.y, z / val.z);
};

Vector3 Vector3::operator/(float val)
{
    return Vector3(x / val, y / val, z / val);
};

Vector3 Vector3::operator+(Vector3 val)
{
    return Vector3(x + val.x, y + val.y, z + val.z);
};

String Vector3::toString()
{
    String xs = String(x);
    String ys = String(y);
    String zs = String(z);

    String ret = "(" + xs + "," + ys + "," + zs + ")";
    return ret;
};

Vector3 Vector3::rotate(int angle, Vector2 pivot)
{
    // Translate line so pivot point is at the origin
    if (angle == 0)
        return Vector3(x, y, z);

    x -= pivot.x;
    y -= pivot.y;
    float angleRad = radians(angle);

    // Rotate point by angle
    int x_rotated = x * cos(angleRad) - y * sin(angleRad);
    int y_rotated = x * sin(angleRad) + y * cos(angleRad);

    // Translate point back to original position
    x = x_rotated + pivot.x;
    y = y_rotated + pivot.y;

    return Vector3(x, y, z);
};

float Vector3::distanceTo(Vector3 v)
{
    double dx = v.x - x;
    double dy = v.y - y;
    double dz = v.z - z;
    return sqrt(dx * dx + dy * dy + dz * dz);
};
