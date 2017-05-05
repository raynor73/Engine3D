#include "transform.h"

Transform::Transform(QObject *parent) :
	QObject(parent),
	m_translation(Vector3f(0, 0, 0)),
	m_rotation(Quaternion(0, 0, 0, 1)),
	m_scale(Vector3f(1, 1, 1))
{}

Matrix4f Transform::transformation() const
{
	Matrix4f translationM;
	translationM.initTranslation(m_translation.x, m_translation.y, m_translation.z);

	Matrix4f rotationM;
	//rotationM = m_rotation.toRotationMatrix();
	//rotationM.initRotation(m_rotation.x, m_rotation.y, m_rotation.z);

	Matrix4f scaleM;
	scaleM.initScale(m_scale.x, m_scale.y, m_scale.z);

	return translationM * rotationM * scaleM;
}
