#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QObject>
#include "geometry/vector3f.h"
#include "geometry/matrix4f.h"

class Transform : public QObject
{
	Q_OBJECT
public:
	explicit Transform(float, float, float, float, float, QObject *parent = 0);

	Vector3f *translation() { return &m_translation; }
	void setTranslation(const Vector3f &);
	void setTranslation(float, float, float);
	Vector3f *rotation() { return &m_rotation; }
	void setRotation(const Vector3f &);
	void setRotation(float, float, float);
	Vector3f *scale() { return &m_scale; }
	void setScale(const Vector3f &);
	void setScale(float, float, float);
	Matrix4f transformation();
	Matrix4f projectedTransformation();

private:
	Vector3f m_translation;
	Vector3f m_rotation;
	Vector3f m_scale;

	float m_zNear;
	float m_zFar;
	float m_width;
	float m_height;
	float m_fov;
};

#endif // TRANSFORM_H