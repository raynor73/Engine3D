#include "transform.h"

Transform::Transform(QObject *parent) :
	QObject(parent),
	m_translation(Vector3f(0, 0, 0)),
	m_rotation(Vector3f(0, 0, 0))
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


Matrix4f Transform::transformation()
{
	Matrix4f translationM;
	translationM.initTranslation(m_translation.x, m_translation.y, m_translation.z);

	Matrix4f rotationM;
	rotationM.initRotation(m_rotation.x, m_rotation.y, m_rotation.z);

	return translationM * rotationM;
}
