#include "camera.h"

Camera::Camera(const Vector3f &position, const Vector3f &formard, const Vector3f &up,
			   QObject *parent) :
	QObject(parent),
	m_position(position),
	m_forward(formard),
	m_up(up)
{
	m_up = m_up.normalized();
	m_forward = m_forward.normalized();
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

Vector3f Camera::calculateLeft()
{
	Vector3f left = m_forward.cross(m_up);
	left.normalized();
	return left;
}

Vector3f Camera::calculateRight()
{
	Vector3f right = m_up.cross(m_forward);
	right.normalized();
	return right;
}

void Camera::rotateX(float angle)
{
	Vector3f hAxis = yAxis.cross(m_forward).normalized();
	m_forward = m_forward.rotate(angle, hAxis).normalized();
	m_up = m_forward.cross(hAxis).normalized();
}

void Camera::rotateY(float angle)
{
	Vector3f hAxis = yAxis.cross(m_forward).normalized();
	m_forward = m_forward.rotate(angle, yAxis).normalized();
	m_up = m_forward.cross(hAxis).normalized();
}

const Vector3f Camera::yAxis(0, 1, 0);
