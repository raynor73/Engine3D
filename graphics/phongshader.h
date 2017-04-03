#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include <graphics/shader.h>
#include <geometry/vector3f.h>
#include <graphics/directionallight.h>
#include <graphics/camera.h>
#include "qopenglfunctions_selector.h"

class PhongShader : public Shader
{
public:
	PhongShader(QOPENGLFUNCTIONS_CLASSNAME &, const Camera *, QObject *parent = 0);

	virtual void updateUniforms(const Matrix4f &, const Matrix4f &, const Material &);

	Vector3f ambientLight() const { return m_ambientLight; }
	void setAmbientLight(const Vector3f &ambientLight) { m_ambientLight = ambientLight; }
	DirectionalLight directionalLight() const { return m_directionalLight; }
	void setDirectionalLight(const DirectionalLight &directionalLight) { m_directionalLight = directionalLight; }
	const Camera *camera() const { return m_camera; }
	void setCamera(const Camera *camera) { Q_ASSERT(camera != NULL); m_camera = camera; }

	using Shader::setUniform;
	void setUniform(const QString &, const BaseLight &);
	void setUniform(const QString &, const DirectionalLight &);

private:
	Vector3f m_ambientLight;
	DirectionalLight m_directionalLight;
	const Camera *m_camera;
};

#endif // PHONGSHADER_H
