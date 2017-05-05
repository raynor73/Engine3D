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

	explicit Quaternion(QObject *parent = 0);
	Quaternion(float, float, float, float, QObject *parent = 0);
	Quaternion(const Quaternion &);

	Quaternion &operator =(const Quaternion &);

	Matrix4f toRotationMatrix() const;

	Vector3f calculateForward() const;
	Vector3f calculateBack() const;
	Vector3f calculateUp() const;
	Vector3f calculateDown() const;
	Vector3f calculateRight() const;
	Vector3f calculateLeft() const;

	float length();
	Quaternion *normalize();
	Quaternion conjugate();
	Quaternion operator *(const Quaternion &);
	Quaternion operator *(const Vector3f &);

	Quaternion *initRotation(const Vector3f &axis, float angle);
};

#endif // QUATERNION_H
