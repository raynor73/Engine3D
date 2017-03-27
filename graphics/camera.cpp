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

Vector3f Camera::calculateLeft()
{
	Vector3f left = m_up.cross(m_forward);
	left.normalize();
	return left;
}

Vector3f Camera::calculateRight()
{
	Vector3f right = m_forward.cross(m_up);
	right.normalize();
	return right;
}

void Camera::rotateX(float angle)
{
	Vector3f hAxis = yAxis.cross(m_forward);
	hAxis.normalize();

	m_forward.rotate(angle, hAxis);
	m_forward.normalize();

	m_up = m_forward.cross(hAxis);
	m_up.normalize();
}

void Camera::rotateY(float angle)
{
	Vector3f hAxis = yAxis.cross(m_forward);
	hAxis.normalize();

	m_forward.rotate(angle, yAxis);
	m_forward.normalize();

	m_up = m_forward.cross(hAxis);
	m_up.normalize();
}

const Vector3f Camera::yAxis(0, 1, 0);
