#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <engine/core/vector3f.h>

class Camera : public QObject
{
	Q_OBJECT
public:
	static const Vector3f yAxis;

	explicit Camera(QObject *parent = 0);
	explicit Camera(const Vector3f &, const Vector3f &, const Vector3f &, QObject *parent = 0);

	void setPosition(const Vector3f &);
	Vector3f position() const { return m_position; }
	void setForward(const Vector3f &);
	Vector3f forward() const { return m_forward; }
	void setUp(const Vector3f &);
	Vector3f up() { return m_up; }

	void move(const Vector3f &, float);
	Vector3f calculateLeft();
	Vector3f calculateRight();
	void rotateX(float);
	void rotateY(float);

private:
	Vector3f m_position;
	Vector3f m_forward;
	Vector3f m_up;
};

#endif // CAMERA_H
