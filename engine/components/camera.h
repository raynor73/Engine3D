#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <engine/core/vector3f.h>
#include <engine/core/matrix4f.h>
#include <engine/components/gamecomponent.h>

class Camera : public GameComponent
{
	Q_OBJECT
public:
	static const Vector3f yAxis;

	Camera(float fov, float aspectRatio, float zNear, float zFar, QObject *parent = 0);

	virtual void addToRenderingEngine(RenderingEngine &) override;

	void move(const Vector3f &, float);
	Matrix4f calculateViewProjection();

private:
	Matrix4f m_projection;
};

#endif // CAMERA_H
