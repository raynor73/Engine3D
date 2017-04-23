#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QObject>
#include <engine/rendering/camera.h>
#include <engine/core/vector3f.h>
#include <engine/core/matrix4f.h>

class Transform : public QObject
{
	Q_OBJECT
public:
	Transform(QObject *parent = 0);

	Vector3f *translation() { return &m_translation; }
	void setTranslation(const Vector3f &);
	void setTranslation(float, float, float);
	Vector3f *rotation() { return &m_rotation; }
	void setRotation(const Vector3f &);
	void setRotation(float, float, float);
	Vector3f *scale() { return &m_scale; }
	void setScale(const Vector3f &);
	void setScale(float, float, float);
	Matrix4f transformation() const;
//	Matrix4f projectedTransformation(const Camera &) const;

private:
	Vector3f m_translation;
	Vector3f m_rotation;
	Vector3f m_scale;
};

#endif // TRANSFORM_H
