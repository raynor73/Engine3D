#include "camera.h"
#include <engine/rendering/renderingengine.h>

Camera::Camera(float fov, float aspectRatio, float zNear, float zFar, QObject *parent) :
	GameComponent(parent)
{
	m_projection.initPerspective(fov, aspectRatio, zNear, zFar);
}

Matrix4f Camera::calculateViewProjection()
{
	Matrix4f cameraRotation = transform().rotation().toRotationMatrix();
	Matrix4f cameraTranslation;
	Vector3f position = transform().translation();
	cameraTranslation.initTranslation(-position.x, -position.y, -position.z);
	return m_projection * cameraRotation * cameraTranslation;
}

void Camera::move(const Vector3f &direction, float amount)
{
	transform().setTranslation(transform().translation() + direction * amount);
}

/*Vector3f Camera::calculateLeft()
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
}*/

/*void Camera::rotateX(float angle)
{
	Vector3f hAxis = yAxis.cross(m_forward).normalized();
	m_forward = m_forward.rotate(hAxis, angle).normalized();
	m_up = m_forward.cross(hAxis).normalized();
}

void Camera::rotateY(float angle)
{
	Vector3f hAxis = yAxis.cross(m_forward).normalized();
	m_forward = m_forward.rotate(yAxis, angle).normalized();
	m_up = m_forward.cross(hAxis).normalized();
}*/

void Camera::addToRenderingEngine(RenderingEngine &renderingEngine)
{
	renderingEngine.setCamera(this);
}

const Vector3f Camera::yAxis(0, 1, 0);
