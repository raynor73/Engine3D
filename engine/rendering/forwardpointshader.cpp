#include "forwardpointshader.h"
#include <engine/core/renderingengine.h>

ForwardPointShader::ForwardPointShader(QOPENGLFUNCTIONS_CLASSNAME &f,
									   RenderingEngine &renderingEngine, QObject *parent) :
	Shader(f, renderingEngine, parent)
{
	setVertexShaderFromFile("forwardpoint.vsh");
	setFragmentShaderFromFile("forwardpoint.fsh");
	linkProgram();

	addUniform("model");
	addUniform("modelViewProjection");

	addUniform("specularIntensity");
	addUniform("specularPower");
	addUniform("eyePosition");

	addUniform("pointLight.base.color");
	addUniform("pointLight.base.intensity");
	addUniform("pointLight.attenuation.constant");
	addUniform("pointLight.attenuation.linear");
	addUniform("pointLight.attenuation.exponent");
	addUniform("pointLight.position");
	addUniform("pointLight.range");
}

void ForwardPointShader::updateUniforms(const Transform &transform, Camera &camera, const Material &material)
{
	Matrix4f worldMatrix = transform.transformation();
	Matrix4f projectedMatrix = camera.calculateViewProjection() * worldMatrix;

	material.texture()->bind();

	setUniform("model", worldMatrix);
	setUniform("modelViewProjection", projectedMatrix);

	setUniformf("specularIntensity", material.specularIntensity());
	setUniformf("specularPower", material.specularPower());

	setUniform("eyePosition", camera.position());

	setUniform("pointLight", m_renderingEngine.pointLight());
}

void ForwardPointShader::setUniform(const QString &uniformName, const BaseLight &baseLight)
{
	setUniform(uniformName + ".color", baseLight.color());
	setUniformf(uniformName + ".intensity", baseLight.intensity());
}

void ForwardPointShader::setUniform(const QString &uniformName, const PointLight &pointLight)
{
	setUniform(uniformName + ".base", pointLight.baseLight());
	setUniformf(uniformName + ".attenuation.constant", pointLight.attenuation().constant());
	setUniformf(uniformName + ".attenuation.linear", pointLight.attenuation().linear());
	setUniformf(uniformName + ".attenuation.exponent", pointLight.attenuation().exponent());
	setUniform(uniformName + ".position", pointLight.position());
	setUniformf(uniformName + ".range", pointLight.range());
}
