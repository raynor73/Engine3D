#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <QObject>

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
	float length();
	float dot(const Vector3f &);
	Vector3f cross(const Vector3f &);
	Vector3f *normalize();
	Vector3f rotate(float);
	Vector3f operator +(const Vector3f &);
	Vector3f operator +(float);
	Vector3f operator -(const Vector3f &);
	Vector3f operator -(float);
	Vector3f operator *(const Vector3f &);
	Vector3f operator *(float) const;
	Vector3f operator /(const Vector3f &);
	Vector3f operator /(float);
	Vector3f &operator =(const Vector3f &);
};

#endif // VECTOR3F_H
