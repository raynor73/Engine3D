#include "transform.h"

Transform::Transform(QObject *parent) :
	QObject(parent),
	m_parentTransformation(NULL),
	m_translation(Vector3f(0, 0, 0)),
	m_rotation(Quaternion(0, 0, 0, 1)),
	m_scale(Vector3f(1, 1, 1)),
	m_hasChanged(true)
{
	m_parentMatrix.initIdentity();
}

Matrix4f Transform::transformation()
{
	Matrix4f translationM;
	translationM.initTranslation(m_translation.x, m_translation.y, m_translation.z);

	Matrix4f rotationM;
	rotationM = m_rotation.toRotationMatrix();

	Matrix4f scaleM;
	scaleM.initScale(m_scale.x, m_scale.y, m_scale.z);

	if (m_parentTransformation != NULL && m_parentTransformation->hasChanged()) {
		m_parentTransformation->setHasChanged(false);
		m_parentMatrix = m_parentTransformation->transformation();
	}

	return m_parentMatrix * translationM * rotationM * scaleM;
}

bool Transform::hasChanged() const
{
	if (m_parentTransformation != NULL && m_parentTransformation->hasChanged())

		return true;
	return m_hasChanged;
}
