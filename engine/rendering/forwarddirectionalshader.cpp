#include "forwarddirectionalshader.h"
#include <engine/rendering/renderingengine.h>

ForwardDirectionalShader::ForwardDirectionalShader(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint vertexArrayName,
												   QObject *parent) :
	Shader(f, vertexArrayName, parent)
{
	QString vertexShaderText = loadShader("forwarddirectional.vsh");
	QString fragmentShaderText = loadShader("forwarddirectional.fsh");

	setVertexShader(vertexShaderText);
	setFragmentShader(fragmentShaderText);
	linkProgram();

	/*addUniform("model");
	addUniform("modelViewProjection");

	addUniform("specularIntensity");
	addUniform("specularPower");
	addUniform("eyePosition");*/

	addAllUniforms(vertexShaderText);
	addAllUniforms(fragmentShaderText);

	addUniform("directionalLight.base.color");
	addUniform("directionalLight.base.intensity");
	addUniform("directionalLight.direction");
}

void ForwardDirectionalShader::updateUniforms(Transform &transform, Material &material,
											  RenderingEngine &renderingEngine)
{
	Camera &camera = renderingEngine.mainCamera();

	Matrix4f worldMatrix = transform.transformation();
	Matrix4f projectedMatrix = camera.calculateViewProjection() * worldMatrix;

	material.findTexture("diffuse")->bind();

	setUniform("model", worldMatrix);
	setUniform("modelViewProjection", projectedMatrix);

	setUniformf("specularIntensity", material.findFloat("specularIntensity"));
	setUniformf("specularPower", material.findFloat("specularPower"));

	setUniform("eyePosition", camera.transform().calculateTransformedTranslation());

	setUniform("directionalLight", static_cast<DirectionalLight &>(*renderingEngine.activeLight()));
}

void ForwardDirectionalShader::setUniform(const QString &uniformName, const BaseLight &baseLight)
{
	setUniform(uniformName + ".color", baseLight.color());
	setUniformf(uniformName + ".intensity", baseLight.intensity());
}

void ForwardDirectionalShader::setUniform(const QString &uniformName, DirectionalLight &directionalLight)
{
	setUniform(uniformName + ".base", static_cast<const BaseLight &>(directionalLight));
	setUniform(uniformName + ".direction", directionalLight.direction());
}
