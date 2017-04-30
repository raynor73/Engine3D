#include "forwarddirectionalshader.h"
#include <engine/core/renderingengine.h>

ForwardDirectionalShader::ForwardDirectionalShader(QOPENGLFUNCTIONS_CLASSNAME &f,
												   RenderingEngine &renderingEngine, QObject *parent) :
	Shader(f, renderingEngine, parent)
{
	setVertexShaderFromFile("forwarddirectional.vsh");
	setFragmentShaderFromFile("forwarddirectional.fsh");
	linkProgram();

	addUniform("model");
	addUniform("modelViewProjection");

	addUniform("specularIntensity");
	addUniform("specularPower");
	addUniform("eyePosition");

	addUniform("directionalLight.base.color");
	addUniform("directionalLight.base.intensity");
	addUniform("directionalLight.direction");
}

void ForwardDirectionalShader::updateUniforms(const Transform &transform, Camera &camera, const Material &material)
{
	Matrix4f worldMatrix = transform.transformation();
	Matrix4f projectedMatrix = camera.calculateViewProjection() * worldMatrix;

	material.texture()->bind();

	setUniform("model", worldMatrix);
	setUniform("modelViewProjection", projectedMatrix);

	setUniformf("specularIntensity", material.specularIntensity());
	setUniformf("specularPower", material.specularPower());

	setUniform("eyePosition", camera.position());

	setUniform("directionalLight", static_cast<DirectionalLight &>(*m_renderingEngine.activeLight()));
}

void ForwardDirectionalShader::setUniform(const QString &uniformName, const BaseLight &baseLight)
{
	setUniform(uniformName + ".color", baseLight.color());
	setUniformf(uniformName + ".intensity", baseLight.intensity());
}

void ForwardDirectionalShader::setUniform(const QString &uniformName, const DirectionalLight &directionalLight)
{
	setUniform(uniformName + ".base", static_cast<const BaseLight &>(directionalLight));
	setUniform(uniformName + ".direction", directionalLight.direction());
}
