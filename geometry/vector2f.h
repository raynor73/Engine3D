#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <QObject>
#include <QString>

class Vector2f : public QObject
{
	Q_OBJECT
public:
	float x;
	float y;

	explicit Vector2f(float, float, QObject *parent = 0);
	Vector2f(const Vector2f &);

	operator QString();
	float length();
	float dot(const Vector2f &);
	Vector2f normalized();
	Vector2f rotate(float);
	Vector2f operator +(const Vector2f &);
	Vector2f operator +(float);
	Vector2f operator -(const Vector2f &);
	Vector2f operator -(float);
	Vector2f operator *(const Vector2f &);
	Vector2f operator *(float);
	Vector2f operator /(const Vector2f &);
	Vector2f operator /(float);
	Vector2f &operator =(const Vector2f &);
};

#endif // VECTOR2F_H
