#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include "geometry/vector3f.h"

class Camera : public QObject
{
	Q_OBJECT
public:
	static const Vector3f yAxis;

	explicit Camera(QObject *parent = 0);
	explicit Camera(const Vector3f &, const Vector3f &, const Vector3f &, QObject *parent = 0);

	void setPosition(const Vector3f &);
	Vector3f position() { return m_position; }
	void setForward(const Vector3f &);
	Vector3f forward() { return m_forward; }
	void setUp(const Vector3f &);
	Vector3f up() { return m_up; }

	void move(const Vector3f &, float);

private:
	Vector3f m_position;
	Vector3f m_forward;
	Vector3f m_up;
};

#endif // CAMERA_H
