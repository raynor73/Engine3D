#include <cmath>
#include "quaternion.h"

Quaternion::Quaternion(QObject *parent) : Quaternion(0, 0, 0, 1, parent)
{}

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

Quaternion *Quaternion::initRotation(const Vector3f &axis, float angle)
{
	float sinHalfAngle = std::sin(angle / 2);
	float cosHalfAngle = std::cos(angle / 2);

	x = axis.x * sinHalfAngle;
	y = axis.y * sinHalfAngle;
	z = axis.z * sinHalfAngle;
	w = cosHalfAngle;

	return this;
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

