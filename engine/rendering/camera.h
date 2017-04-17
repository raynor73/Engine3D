#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <engine/core/vector3f.h>
#include <engine/core/matrix4f.h>

class Camera : public QObject
{
	Q_OBJECT
public:
	static const Vector3f yAxis;

	Camera(float fov, float aspectRatio, float zNear, float zFar, QObject *parent = 0);

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
	Matrix4f m_projection;
};

#endif // CAMERA_H
