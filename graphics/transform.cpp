#include "transform.h"

Transform::Transform(QObject *parent) :
	QObject(parent),
	m_translation(Vector3f(0, 0, 0))
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

Matrix4f Transform::transformation()
{
	Matrix4f translationM;
	translationM.initTranslation(m_translation.x, m_translation.y, m_translation.z);
	return translationM;
}
