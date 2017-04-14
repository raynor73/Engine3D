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
	explicit Transform(Camera &, float, float, float, QObject *parent = 0);

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
	void setDisplaySize(float, float);

private:
	Vector3f m_translation;
	Vector3f m_rotation;
	Vector3f m_scale;

	float m_zNear;
	float m_zFar;
	float m_displayWidth;
	float m_displayHeight;
	float m_fov;

	Camera &m_camera;

	bool m_isDisplaySizeKnown;
};

#endif // TRANSFORM_H
