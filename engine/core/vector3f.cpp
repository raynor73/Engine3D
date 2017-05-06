#include <cmath>
#include <engine/core/vector3f.h>
#include <utils.h>
#include <engine/core/quaternion.h>
#include <float.h>
#include <cmath>

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

Vector3f Vector3f::lerp(const Vector3f &destination, float lerpFactor)
{
	return ((destination - (*this)) * lerpFactor) + (*this);
}

float Vector3f::length() const
{
	return sqrtf(x * x + y * y + z * z);
}

float Vector3f::max() const
{
	return std::max(x, std::max(y ,z));
}

float Vector3f::dot(const Vector3f &other) const
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

Vector3f Vector3f::rotate(const Vector3f &axis, float angle) const
{
	float sinAngle = std::sin(-angle);
	float cosAngle = std::cos(-angle);

	return this->cross(axis * sinAngle) + ((*this) * cosAngle) + (axis * (this->dot(axis * (1 - cosAngle))));
}

Vector3f Vector3f::rotate(const Quaternion &rotation) const
{
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

bool Vector3f::operator ==(const Vector3f &other) const
{
	return
			std::abs(x - other.x) < FLT_EPSILON &&
			std::abs(y - other.y) < FLT_EPSILON &&
			std::abs(z - other.z) < FLT_EPSILON;
}
