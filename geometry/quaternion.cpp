#include <cmath>
#include "quaternion.h"

Quaternion::Quaternion(float x, float y, float z, float w, QObject *parent) :
    QObject(parent),
    x(x),
    y(y),
    z(z),
    w(w)
{}

Quaternion::Quaternion(const Quaternion &other) :
    QObject(other.parent()),
    x(other.x),
    y(other.y),
    z(other.z),
    w(other.w)
{}

float Quaternion::length()
{
    return sqrtf(x * x + y * y + z * z + w * w);
}

Quaternion *Quaternion::normalize()
{
    float l = length();

    x /= l;
    y /= l;
    z /= l;
    w /= l;

    return this;
}

Quaternion Quaternion::conjugate()
{
    return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::operator *(const Quaternion &other)
{
    float newW = w * other.w - x * other.x - y * other.y - z * other.z;
    float newX = x * other.w + w * other.x + y * other.z - z * other.y;
    float newY = y * other.w + w * other.y + z * other.x - x * other.z;
    float newZ = z * other.w + w * other.z + x * other.y - y * other.x;

    return Quaternion(newX, newY, newZ, newW);
}

Quaternion Quaternion ::operator *(const Vector3f &v)
{
    float newW = -x * v.x - y * v.y - z * v.z;
    float newX =  w * v.x + y * v.z - z * v.y;
    float newY =  w * v.y + z * v.x - x * v.z;
    float newZ =  w * v.z + x * v.y - y * v.x;

    return Quaternion(newX, newY, newZ, newW);
}
