#include <cmath>
#include <float.h>
#include <utils.h>
#include <engine/core/vector2f.h>

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

Vector2f Vector2f::lerp(const Vector2f &destination, float lerpFactor)
{
	return ((destination - (*this)) * lerpFactor) + (*this);
}

Vector2f Vector2f::abs()
{
	return Vector2f(std::abs(x), std::abs(y));
}

Vector2f Vector2f::normalized()
{
	return Vector2f(*this) / length();
}

float Vector2f::cross(const Vector2f &other) const
{
	return x * other.y - y * other.x;
}

Vector2f Vector2f::rotate(float angle)
{
	float rad = Utils::toRadians(angle);
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

Vector2f Vector2f::operator -(const Vector2f &other) const
{
	return Vector2f(x - other.x, y - other.y);
}

Vector2f Vector2f::operator -(float a)
{
	return Vector2f(x - a, y - a);
}

Vector2f Vector2f::operator *(const Vector2f &other) const
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

Vector2f &Vector2f::operator =(const Vector2f &other)
{
	if (&other == this)
		return *this;

	x = other.x;
	y = other.y;

	return *this;
}

bool Vector2f::operator ==(const Vector2f &other) const
{
	return
			std::abs(x - other.x) < FLT_EPSILON &&
			std::abs(y - other.y) < FLT_EPSILON;
}
