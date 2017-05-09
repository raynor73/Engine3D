#include <cmath>
#include <float.h>
#include "quaternion.h"

Quaternion::Quaternion(float x, float y, float z, float w, QObject *parent) :
	QObject(parent),
	x(x),
	y(y),
	z(z),
	w(w)
{}

Quaternion::Quaternion(const Vector3f &axis, float angle, QObject *parent) :
	QObject(parent)
{
	float sinHalfAngle = std::sin(angle / 2);
	float cosHalfAngle = std::cos(angle / 2);

	x = axis.x * sinHalfAngle;
	y = axis.y * sinHalfAngle;
	z = axis.z * sinHalfAngle;
	w = cosHalfAngle;
}

Quaternion::Quaternion(const Quaternion &other) :
	QObject(other.parent()),
	x(other.x),
	y(other.y),
	z(other.z),
	w(other.w)
{}

float Quaternion::length() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::normalized() const
{
	float l = length();
	return Quaternion(x / l, y / l, z / l, w / l);
}

Quaternion Quaternion::conjugate() const
{
	return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::operator *(const Quaternion &other) const
{
	float newW = w * other.w - x * other.x - y * other.y - z * other.z;
	float newX = x * other.w + w * other.x + y * other.z - z * other.y;
	float newY = y * other.w + w * other.y + z * other.x - x * other.z;
	float newZ = z * other.w + w * other.z + x * other.y - y * other.x;

	return Quaternion(newX, newY, newZ, newW);
}

Quaternion Quaternion ::operator *(const Vector3f &v) const
{
	float newW = -x * v.x - y * v.y - z * v.z;
	float newX =  w * v.x + y * v.z - z * v.y;
	float newY =  w * v.y + z * v.x - x * v.z;
	float newZ =  w * v.z + x * v.y - y * v.x;

	return Quaternion(newX, newY, newZ, newW);
}

Quaternion &Quaternion::operator =(const Quaternion &other)
{
	if (this == &other)
		return *this;

	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;

	return *this;
}

Vector3f Quaternion::calculateForward() const
{
	return Vector3f(2 * (x * z - w * y), 2 * (y * z + w * x), 1 - 2 * (x * x + y * y));
}

Vector3f Quaternion::calculateBack() const
{
	return Vector3f(-2 * (x * z - w * y), -2 * (y * z + w * x), -(1 - 2 * (x * x + y * y)));
}

Vector3f Quaternion::calculateUp() const
{
	return Vector3f(2 * (x * y + w * z), 1 - 2 * (x * x + z * z), 2.0f * (y * z - w * x));
}

Vector3f Quaternion::calculateDown() const
{
	return Vector3f(-2 * (x * y + w * z), -(1 - 2 * (x * x + z * z)), -2.0f * (y * z - w * x));
}

Vector3f Quaternion::calculateRight() const
{
	return Vector3f(1 - 2 * (y * y + z * z), 2 * (x * y - w * z), 2 * (x * z + w * y));
}

Vector3f Quaternion::calculateLeft() const
{
	return Vector3f(-(1 - 2 * (y * y + z * z)), -2 * (x * y - w * z), -2 * (x * z + w * y));
}

Matrix4f Quaternion::toRotationMatrix() const
{
	return *Matrix4f().initRotation(calculateForward(), calculateUp(), calculateRight());
}

bool Quaternion::operator ==(const Quaternion &other) const
{
	return
			std::abs(x - other.x) < FLT_EPSILON &&
			std::abs(y - other.y) < FLT_EPSILON &&
			std::abs(z - other.z) < FLT_EPSILON &&
			std::abs(w - other.w) < FLT_EPSILON;
}

bool Quaternion::operator !=(const Quaternion &other) const
{
	return !((*this) == other);
}
