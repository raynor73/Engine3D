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

//From Ken Shoemake's "Quaternion Calculus and Fast Animation" article
Quaternion::Quaternion(const Matrix4f &rotation, QObject *parent) :
	QObject(parent)
{
	float trace = rotation.get(0, 0) + rotation.get(1, 1) + rotation.get(2, 2);

	if (trace > 0) {
		float s = 0.5 / std::sqrt(trace + 1);
		w = 0.25 / s;
		x = (rotation.get(1, 2) - rotation.get(2, 1)) * s;
		y = (rotation.get(2, 0) - rotation.get(0, 2)) * s;
		z = (rotation.get(0, 1) - rotation.get(1, 0)) * s;
	} else {
		if (rotation.get(0, 0) > rotation.get(1, 1) && rotation.get(0, 0) > rotation.get(2, 2)) {
			float s = 2 * std::sqrt(1 + rotation.get(0, 0) - rotation.get(1, 1) - rotation.get(2, 2));
			w = (rotation.get(1, 2) - rotation.get(2, 1)) / s;
			x = 0.25 * s;
			y = (rotation.get(1, 0) + rotation.get(0, 1)) / s;
			z = (rotation.get(2, 0) + rotation.get(0, 2)) / s;
		} else if(rotation.get(1, 1) > rotation.get(2, 2)) {
			float s = 2 * std::sqrt(1 + rotation.get(1, 1) - rotation.get(0, 0) - rotation.get(2, 2));
			w = (rotation.get(2, 0) - rotation.get(0, 2)) / s;
			x = (rotation.get(1, 0) + rotation.get(0, 1)) / s;
			y = 0.25 * s;
			z = (rotation.get(2, 1) + rotation.get(1, 2)) / s;
		} else {
			float s = 2 * std::sqrt(1 + rotation.get(2, 2) - rotation.get(0, 0) - rotation.get(1, 1));
			w = (rotation.get(0, 1) - rotation.get(1, 0) ) / s;
			x = (rotation.get(2, 0) + rotation.get(0, 2) ) / s;
			y = (rotation.get(1, 2) + rotation.get(2, 1) ) / s;
			z = 0.25 * s;
		}
	}

	float length = std::sqrt(x * x + y * y + z * z + w * w);
	x /= length;
	y /= length;
	z /= length;
	w /= length;
}

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

Quaternion Quaternion::operator *(float multiplier) const
{
	return Quaternion(x * multiplier, y * multiplier, z * multiplier, w * multiplier);
}

Quaternion Quaternion::operator -(const Quaternion &other) const
{
	return Quaternion(x - other.x, y - other.y, z - other.z, w - other.w);
}

Quaternion Quaternion::operator +(const Quaternion &other) const
{
	return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w);
}

float Quaternion::dot(const Quaternion &other) const
{
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

Quaternion Quaternion ::operator *(const Vector3f &v) const
{
	float newW = -x * v.x - y * v.y - z * v.z;
	float newX =  w * v.x + y * v.z - z * v.y;
	float newY =  w * v.y + z * v.x - x * v.z;
	float newZ =  w * v.z + x * v.y - y * v.x;

	return Quaternion(newX, newY, newZ, newW);
}

Quaternion Quaternion::nlerp(const Quaternion &destination, float factor, bool shortestRequired)
{
	Quaternion result = destination;

	if (shortestRequired && this->dot(destination) < 0)
		result = Quaternion(-destination.x, -destination.y, -destination.z, -destination.w);

	return ((result - (*this)) * factor + (*this)).normalized();
}

Quaternion Quaternion::slerp(const Quaternion &destination, float factor, bool shortestRequired)
{
	float cos = this->dot(destination);
	Quaternion correctedDestination = destination;

	if (shortestRequired && cos < 0) {
		cos = -cos;
		correctedDestination = Quaternion(-destination.x, -destination.y, -destination.z, -destination.w);
	}

	if (std::abs(cos) >= 1 - FLT_EPSILON)
		return nlerp(correctedDestination, factor, false);

	float sin = std::sqrt(1 - cos * cos);
	float angle = std::atan2(sin, cos);
	float invertedSin =  1 / sin;

	float sourceFactor = std::sin((1 - factor) * angle) * invertedSin;
	float destinationFactor = std::sin(factor * angle) * invertedSin;

	return (((*this) * sourceFactor) + correctedDestination) * destinationFactor;
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
	return Vector3f(0, 0, 1).rotate(*this);
}

Vector3f Quaternion::calculateBack() const
{
	return Vector3f(0, 0, -1).rotate(*this);
}

Vector3f Quaternion::calculateUp() const
{
	return Vector3f(0, 1, 0).rotate(*this);
}

Vector3f Quaternion::calculateDown() const
{
	return Vector3f(0, -1, 0).rotate(*this);
}

Vector3f Quaternion::calculateRight() const
{
	return Vector3f(1, 0, 0).rotate(*this);
}

Vector3f Quaternion::calculateLeft() const
{
	return Vector3f(-1, 0, 0).rotate(*this);
}

Matrix4f Quaternion::toRotationMatrix() const
{
	Vector3f forward(2 * (x * z - w * y), 2 * (y * z + w * x), 1 - 2 * (x * x + y * y));
	Vector3f up(2 * (x * y + w * z), 1 - 2 * (x * x + z * z), 2.0f * (y * z - w * x));
	Vector3f right(1 - 2 * (y * y + z * z), 2 * (x * y - w * z), 2 * (x * z + w * y));

	return *Matrix4f().initRotation(forward, up, right);
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
