#include "camera.h"
#include <engine/rendering/renderingengine.h>

Camera::Camera(float fov, float aspectRatio, float zNear, float zFar, QObject *parent) :
	GameComponent(parent)
{
	m_projection.initPerspective(fov, aspectRatio, zNear, zFar);
}

Matrix4f Camera::calculateViewProjection()
{
	Matrix4f cameraRotation = transform().calculateTransformedRotation().conjugate().toRotationMatrix();

	Matrix4f cameraTranslation;
	Vector3f position = transform().calculateTransformedTranslation();
	cameraTranslation.initTranslation(-position.x, -position.y, -position.z);

	return m_projection * cameraRotation * cameraTranslation;
}

void Camera::move(const Vector3f &direction, float amount)
{
	transform().setTranslation(transform().translation() + direction * amount);
}

void Camera::addToRenderingEngine(RenderingEngine &renderingEngine)
{
	renderingEngine.setCamera(this);
}

const Vector3f Camera::yAxis(0, 1, 0);
