#include "camera.h"

Camera::Camera(const Vector3f &position, const Vector3f &formard, const Vector3f &up,
			   QObject *parent) :
	QObject(parent),
	m_position(position),
	m_forward(formard),
	m_up(up)
{
	m_up.normalize();
	m_forward.normalize();
}

Camera::Camera(QObject *parent) :
	Camera(Vector3f(0, 0, 0), Vector3f(0, 0, 1), Vector3f(0, 1, 0), parent)
{}

void Camera::setPosition(const Vector3f &position)
{
	m_position = position;
}

void Camera::setForward(const Vector3f &forward)
{
	m_forward = forward;
}

void Camera::setUp(const Vector3f &up)
{
	m_up = up;
}

void Camera::move(const Vector3f &direction, float amount)
{
	m_position = m_position + direction * amount;
}

const Vector3f Camera::yAxis(0, 1, 0);
