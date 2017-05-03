#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <QObject>
#include <engine/core/vector2f.h>

class Vector3f : public QObject
{
	Q_OBJECT
public:
	float x;
	float y;
	float z;

	explicit Vector3f(float, float, float, QObject *parent = 0);
	Vector3f(const Vector3f &);

	operator QString();
	float length() const;
	float max() const;
	float dot(const Vector3f &);
	Vector3f abs();
	Vector3f cross(const Vector3f &) const;
	Vector3f normalized() const;
	Vector3f rotate(float, const Vector3f &);
	Vector2f xy() const { return Vector2f(x, y); }
	Vector2f yz() const { return Vector2f(y, z); }
	Vector2f zx() const { return Vector2f(z, x); }
	Vector2f yx() const { return Vector2f(y, x); }
	Vector2f zy() const { return Vector2f(z, y); }
	Vector2f xz() const { return Vector2f(x, z); }
	Vector3f lerp(const Vector3f &, float);
	Vector3f operator +(const Vector3f &);
	Vector3f operator +(float);
	Vector3f operator -(const Vector3f &) const;
	Vector3f operator -(float);
	Vector3f operator *(const Vector3f &);
	Vector3f operator *(float) const;
	Vector3f operator /(const Vector3f &);
	Vector3f operator /(float);
	Vector3f &operator =(const Vector3f &);
	Vector3f &operator +=(const Vector3f &);
	bool operator ==(const Vector3f &) const;
};

#endif // VECTOR3F_H
