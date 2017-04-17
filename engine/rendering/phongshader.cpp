#include "phongshader.h"
#include <engine/rendering/renderutils.h>

PhongShader::PhongShader(QOPENGLFUNCTIONS_CLASSNAME &f, const Camera *camera, QObject *parent) :
	Shader(f, parent),
	m_ambientLight(Vector3f(1, 1, 1)),
	m_directionalLight(DirectionalLight(BaseLight(Vector3f(1, 1, 1), 0), Vector3f(0, 0, 0))),
	m_camera(camera)
{
	Q_ASSERT(camera != NULL);

	setVertexShaderFromFile("phongvertex.vsh");
	setFragmentShaderFromFile("phongfragment.fsh");
	linkProgram();

	addUniform("transform");
	addUniform("transformProjected");
	addUniform("baseColor");
	addUniform("ambientLight");

	addUniform("specularIntensity");
	addUniform("specularPower");
	addUniform("eyePosition");

	addUniform("directionalLight.base.color");
	addUniform("directionalLight.base.intensity");
	addUniform("directionalLight.direction");

	for (int i = 0; i < MAX_POINT_LIGHTS; i++) {
		addUniform(QString("pointLights[%1].base.color").arg(i));
		addUniform(QString("pointLights[%1].base.intensity").arg(i));
		addUniform(QString("pointLights[%1].attenuation.constant").arg(i));
		addUniform(QString("pointLights[%1].attenuation.linear").arg(i));
		addUniform(QString("pointLights[%1].attenuation.exponent").arg(i));
		addUniform(QString("pointLights[%1].position").arg(i));
		addUniform(QString("pointLights[%1].range").arg(i));
	}

	for (int i = 0; i < MAX_SPOT_LIGHTS; i++) {
		addUniform(QString("spotLights[%1].pointLight.base.color").arg(i));
		addUniform(QString("spotLights[%1].pointLight.base.intensity").arg(i));
		addUniform(QString("spotLights[%1].pointLight.attenuation.constant").arg(i));
		addUniform(QString("spotLights[%1].pointLight.attenuation.linear").arg(i));
		addUniform(QString("spotLights[%1].pointLight.attenuation.exponent").arg(i));
		addUniform(QString("spotLights[%1].pointLight.position").arg(i));
		addUniform(QString("spotLights[%1].pointLight.range").arg(i));

		addUniform(QString("spotLights[%1].direction").arg(i));
		addUniform(QString("spotLights[%1].cutoff").arg(i));
	}
}

void PhongShader::setPointLights(const QList<PointLight *> &pointLights)
{
	Q_ASSERT(pointLights.size() <= MAX_POINT_LIGHTS);

	m_pointLights = pointLights;
}

void PhongShader::setSpotLights(const QList<SpotLight *> &spotLights)
{
	Q_ASSERT(spotLights.size() <= MAX_SPOT_LIGHTS);

	m_spotLights = spotLights;
}

void PhongShader::updateUniforms(const Matrix4f &worldMatrix, const Matrix4f &projectedMatrix, const Material &material)
{
	material.texture()->bind();

	setUniform("transformProjected", projectedMatrix);
	setUniform("transform", worldMatrix);
	setUniform("baseColor", material.color());

	setUniform("ambientLight", m_ambientLight);
	setUniform("directionalLight", m_directionalLight);
	for (int i = 0; i < m_pointLights.size(); i++)
		setUniform(QString("pointLights[%1]").arg(i), *m_pointLights.at(i));
	for (int i = 0; i < m_spotLights.size(); i++)
		setUniform(QString("spotLights[%1]").arg(i), *m_spotLights.at(i));

	setUniformf("specularIntensity", material.specularIntensity());
	setUniformf("specularPower", material.specularPower());

	setUniform("eyePosition", m_camera->position());
}

void PhongShader::setUniform(const QString &uniformName, const BaseLight &baseLight)
{
	setUniform(uniformName + ".color", baseLight.color());
	setUniformf(uniformName + ".intensity", baseLight.intensity());
}

void PhongShader::setUniform(const QString &uniformName, const DirectionalLight &directionalLight)
{
	setUniform(uniformName + ".base", directionalLight.base());
	setUniform(uniformName + ".direction", directionalLight.direction());
}

void PhongShader::setUniform(const QString &uniformName, const PointLight &pointLight)
{
	setUniform(uniformName + ".base", pointLight.baseLight());
	setUniformf(uniformName + ".attenuation.constant", pointLight.attenuation().constant());
	setUniformf(uniformName + ".attenuation.linear", pointLight.attenuation().linear());
	setUniformf(uniformName + ".attenuation.exponent", pointLight.attenuation().exponent());
	setUniform(uniformName + ".position", pointLight.position());
	setUniformf(uniformName + ".range", pointLight.range());
}

void PhongShader::setUniform(const QString &uniformName, SpotLight &spotLight)
{
	setUniform(uniformName + ".pointLight", spotLight.pointLight());

	setUniform(uniformName + ".direction", spotLight.direction());
	setUniformf(uniformName + ".cutoff", spotLight.cutoff());
}
