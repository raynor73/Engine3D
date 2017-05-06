#include "forwardspotshader.h"
#include <engine/rendering/renderingengine.h>

ForwardSpotShader::ForwardSpotShader(QOPENGLFUNCTIONS_CLASSNAME &f,
									 RenderingEngine &renderingEngine, QObject *parent) :
	Shader(f, renderingEngine, parent)
{
	setVertexShaderFromFile("forwardspot.vsh");
	setFragmentShaderFromFile("forwardspot.fsh");
	linkProgram();

	addUniform("model");
	addUniform("modelViewProjection");

	addUniform("specularIntensity");
	addUniform("specularPower");
	addUniform("eyePosition");

	addUniform("spotLight.pointLight.base.color");
	addUniform("spotLight.pointLight.base.intensity");
	addUniform("spotLight.pointLight.attenuation.constant");
	addUniform("spotLight.pointLight.attenuation.linear");
	addUniform("spotLight.pointLight.attenuation.exponent");
	addUniform("spotLight.pointLight.position");
	addUniform("spotLight.pointLight.range");
	addUniform("spotLight.direction");
	addUniform("spotLight.cutoff");
}

void ForwardSpotShader::updateUniforms(const Transform &transform, Camera &camera, const Material &material)
{
	Matrix4f worldMatrix = transform.transformation();
	Matrix4f projectedMatrix = camera.calculateViewProjection() * worldMatrix;

	material.texture()->bind();

	setUniform("model", worldMatrix);
	setUniform("modelViewProjection", projectedMatrix);

	setUniformf("specularIntensity", material.specularIntensity());
	setUniformf("specularPower", material.specularPower());

	setUniform("eyePosition", camera.transform().translation());

	setUniform("spotLight", static_cast<SpotLight &>(*m_renderingEngine.activeLight()));
}

void ForwardSpotShader::setUniform(const QString &uniformName, const BaseLight &baseLight)
{
	setUniform(uniformName + ".color", baseLight.color());
	setUniformf(uniformName + ".intensity", baseLight.intensity());
}

void ForwardSpotShader::setUniform(const QString &uniformName, PointLight &pointLight)
{
	setUniform(uniformName + ".base", static_cast<const BaseLight &>(pointLight));
	setUniformf(uniformName + ".attenuation.constant", pointLight.attenuation().constant());
	setUniformf(uniformName + ".attenuation.linear", pointLight.attenuation().linear());
	setUniformf(uniformName + ".attenuation.exponent", pointLight.attenuation().exponent());
	setUniform(uniformName + ".position", pointLight.transform().translation());
	setUniformf(uniformName + ".range", pointLight.range());
}

void ForwardSpotShader::setUniform(const QString &uniformName, SpotLight &spotLight)
{
	setUniform(uniformName + ".pointLight", static_cast<PointLight &>(spotLight));
	setUniform(uniformName + ".direction", spotLight.direction());
	setUniformf(uniformName + ".cutoff", spotLight.cutoff());
}
