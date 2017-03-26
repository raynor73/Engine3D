#include "transform.h"

Transform::Transform(float fov, float width, float height, float zNear, float zFar, QObject *parent) :
	QObject(parent),
	m_translation(Vector3f(0, 0, 0)),
	m_rotation(Vector3f(0, 0, 0)),
	m_scale(Vector3f(1, 1, 1)),
	m_zNear(zNear),
	m_zFar(zFar),
	m_width(width),
	m_height(height),
	m_fov(fov)
{}

void Transform::setTranslation(const Vector3f &translation)
{
	m_translation = translation;
}

void Transform::setTranslation(float x, float y, float z)
{
	m_translation.x = x;
	m_translation.y = y;
	m_translation.z = z;
}

void Transform::setRotation(const Vector3f &rotation)
{
	m_rotation = rotation;
}

void Transform::setRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

void Transform::setScale(const Vector3f &scale)
{
	m_scale = scale;
}

void Transform::setScale(float x, float y, float z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}

Matrix4f Transform::transformation()
{
	Matrix4f translationM;
	translationM.initTranslation(m_translation.x, m_translation.y, m_translation.z);

	Matrix4f rotationM;
	rotationM.initRotation(m_rotation.x, m_rotation.y, m_rotation.z);

	Matrix4f scaleM;
	scaleM.initScale(m_scale.x, m_scale.y, m_scale.z);

	return translationM * rotationM * scaleM;
}

Matrix4f Transform::projectedTransformation()
{
	Matrix4f tansformationM = transformation();

	Matrix4f projection;
	projection.initProjection(m_fov, m_width, m_height, m_zNear, m_zFar);

	return projection * transformation();
}
