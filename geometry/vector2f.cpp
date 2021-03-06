#include <cmath>
#include "vector2f.h"

Vector2f::Vector2f(float x, float y, QObject *parent) :
    QObject(parent),
    x(x),
    y(y)
{}

Vector2f::Vector2f(const Vector2f &other) :
    QObject(other.parent()),
    x(other.x),
    y(other.y)
{}

float Vector2f::length()
{
    return sqrtf(x * x + y * y);
}

float Vector2f::dot(const Vector2f &other)
{
    return x * other.x + y * other.y;
}

Vector2f *Vector2f::normalize()
{
    float l = length();

    x /= l;
    y /= l;

    return this;
}

Vector2f Vector2f::rotate(float angle)
{
    float rad = angle * M_PI / 180;
    float cos = cosf(rad);
    float sin = sinf(rad);
    return Vector2f(x * cos - y * sin, x * sin + y * cos);
}

Vector2f Vector2f::operator +(const Vector2f &other)
{
    return Vector2f(x + other.x, y + other.y);
}

Vector2f Vector2f::operator +(float a)
{
    return Vector2f(x + a, y + a);
}

Vector2f Vector2f::operator -(const Vector2f &other)
{
    return Vector2f(x - other.x, y - other.y);
}

Vector2f Vector2f::operator -(float a)
{
    return Vector2f(x - a, y - a);
}

Vector2f Vector2f::operator *(const Vector2f &other)
{
    return Vector2f(x * other.x, y * other.y);
}

Vector2f Vector2f::operator *(float a)
{
    return Vector2f(x * a, y * a);
}

Vector2f Vector2f::operator /(const Vector2f &other)
{
    return Vector2f(x / other.x, y / other.y);
}

Vector2f Vector2f::operator /(float a)
{
    return Vector2f(x / a, y / a);
}

Vector2f::operator QString()
{
    return QString("%1; %2").arg(x, 0, 'f', 3).arg(y, 0, 'f', 3);
}
