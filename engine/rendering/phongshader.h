#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include <QList>
#include <engine/rendering/shader.h>
#include <engine/core/vector3f.h>
#include <engine/components/directionallight.h>
#include <engine/rendering/camera.h>
#include <engine/components/pointlight.h>
#include "spotlight.h"
#include <engine/rendering/qopenglfunctions_selector.h>

class RenderingEngine;
class PhongShader : public Shader
{
public:
	static const int MAX_POINT_LIGHTS = 4;
	static const int MAX_SPOT_LIGHTS = 4;

	PhongShader(QOPENGLFUNCTIONS_CLASSNAME &, RenderingEngine &, QObject *parent = 0);

	virtual void updateUniforms(const Transform &, Camera &camera, const Material &);

	Vector3f ambientLight() const { return m_ambientLight; }
	void setAmbientLight(const Vector3f &ambientLight) { m_ambientLight = ambientLight; }
	DirectionalLight directionalLight() const { return m_directionalLight; }
	void setDirectionalLight(const DirectionalLight &directionalLight) { m_directionalLight = directionalLight; }
	void setPointLights(const QList<PointLight *> &);
	void setSpotLights(const QList<SpotLight *> &);

	using Shader::setUniform;
	void setUniform(const QString &, const BaseLight &);
	void setUniform(const QString &, const DirectionalLight &);
	void setUniform(const QString &, const PointLight &);
	void setUniform(const QString &, SpotLight &);

private:
	Vector3f m_ambientLight;
	DirectionalLight m_directionalLight;
	QList<PointLight *> m_pointLights;
	QList<SpotLight *> m_spotLights;
};

#endif // PHONGSHADER_H
