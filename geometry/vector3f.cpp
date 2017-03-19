#include <cmath>
#include "vector3f.h"

Vector3f::Vector3f(float x, float y, float z, QObject *parent) :
    QObject(parent),
    x(x),
    y(y),
    z(z)
{}

Vector3f::Vector3f(const Vector3f &other) :
    QObject(other.parent()),
    x(other.x),
    y(other.y),
    z(other.z)
{}

float Vector3f::length()
{
    return sqrtf(x * x + y * y + z * z);
}

