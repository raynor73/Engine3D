#ifndef QUATERNION_H
#define QUATERNION_H

#include <QObject>
#include <engine/core/vector3f.h>
#include <engine/core/matrix4f.h>

class Quaternion : public QObject
{
	Q_OBJECT
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion(const Matrix4f &rotation, QObject *parent = 0);
	Quaternion(float, float, float, float, QObject *parent = 0);
	Quaternion(const Vector3f &axis, float angle, QObject *parent = 0);
	Quaternion(const Quaternion &);

	Quaternion &operator =(const Quaternion &);

	Matrix4f toRotationMatrix() const;

	Vector3f calculateForward() const;
	Vector3f calculateBack() const;
	Vector3f calculateUp() const;
	Vector3f calculateDown() const;
	Vector3f calculateRight() const;
	Vector3f calculateLeft() const;

	float length() const;
	Quaternion normalized() const;
	Quaternion conjugate() const;
	float dot(const Quaternion &) const;
	Quaternion nlerp(const Quaternion &destination, float factor, bool shortestRequired);
	Quaternion slerp(const Quaternion &destination, float factor, bool shortestRequired);
	Quaternion operator *(const Quaternion &) const;
	Quaternion operator -(const Quaternion &) const;
	Quaternion operator +(const Quaternion &) const;
	Quaternion operator *(const Vector3f &) const;
	Quaternion operator *(float) const;
	bool operator ==(const Quaternion &) const;
	bool operator !=(const Quaternion &) const;
};

#endif // QUATERNION_H
