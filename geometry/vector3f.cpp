#include <cmath>
#include "vector3f.h"
#include "utils.h"
#include "geometry/quaternion.h"

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

float Vector3f::length() const
{
    return sqrtf(x * x + y * y + z * z);
}

float Vector3f::dot(const Vector3f &other)
{
    return x * other.x + y * other.y + z * other.z;
}

Vector3f Vector3f::abs()
{
	return Vector3f(std::abs(x), std::abs(y), std::abs(z));
}

Vector3f Vector3f::cross(const Vector3f &other) const
{
    float newX = y * other.z - z * other.y;
    float newY = z * other.x - x * other.z;
    float newZ = x * other.y - y * other.x;

    return Vector3f(newX, newY, newZ);
}

Vector3f Vector3f::normalized() const
{
	return Vector3f(*this) / length();
}

Vector3f Vector3f::rotate(float angle, const Vector3f &axis)
{
	float sinHalfAngle = std::sin(Utils::toRadians(angle / 2));
	float cosHalfAngle = std::cos(Utils::toRadians(angle / 2));

	float rX = axis.x * sinHalfAngle;
	float rY = axis.y * sinHalfAngle;
	float rZ = axis.z * sinHalfAngle;
	float rW = cosHalfAngle;

	Quaternion rotation(rX, rY, rZ, rW);
	Quaternion conjugate = rotation.conjugate();

	Quaternion w = rotation * (*this) * conjugate;

	return Vector3f(w.x, w.y, w.z);
}

Vector3f Vector3f::operator +(const Vector3f &other)
{
    return Vector3f(x + other.x, y + other.y, z + other.z);
}

Vector3f Vector3f::operator +(float a)
{
    return Vector3f(x + a, y + a, z + a);
}

Vector3f Vector3f::operator -(const Vector3f &other) const
{
    return Vector3f(x - other.x, y - other.y, z - other.z);
}

Vector3f Vector3f::operator -(float a)
{
    return Vector3f(x - a, y - a, z - a);
}

Vector3f Vector3f::operator *(const Vector3f &other)
{
    return Vector3f(x * other.x, y * other.y, z * other.z);
}

Vector3f Vector3f::operator *(float a) const
{
    return Vector3f(x * a, y * a, z * a);
}

Vector3f Vector3f::operator /(const Vector3f &other)
{
    return Vector3f(x / other.x, y / other.y, z / other.z);
}

Vector3f Vector3f::operator /(float a)
{
    return Vector3f(x / a, y / a, z / a);
}

Vector3f::operator QString()
{
    return QString("%1; %2; %3").arg(x, 0, 'f', 3).arg(y, 0, 'f', 3).arg(z, 0, 'f', 3);
}

Vector3f &Vector3f::operator =(const Vector3f &other)
{
	if (&other == this)
		return *this;

	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

Vector3f &Vector3f::operator +=(const Vector3f &other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}
