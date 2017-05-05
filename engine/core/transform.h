#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QObject>
#include <engine/rendering/camera.h>
#include <engine/core/vector3f.h>
#include <engine/core/matrix4f.h>
#include <engine/core/quaternion.h>

class Transform : public QObject
{
	Q_OBJECT
public:
	Transform(QObject *parent = 0);

	Vector3f &translation() { return m_translation; }
	void setTranslation(const Vector3f &translation) { m_translation = translation; }

	Quaternion &rotation() { return m_rotation; }
	void setRotation(const Quaternion &rotation) { m_rotation = rotation; }

	Vector3f &scale() { return m_scale; }
	void setScale(const Vector3f &scale) { m_scale = scale; }

	Matrix4f transformation() const;

private:
	Vector3f m_translation;
	Quaternion m_rotation;
	Vector3f m_scale;
};

#endif // TRANSFORM_H
