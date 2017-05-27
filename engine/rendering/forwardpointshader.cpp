#include "forwardpointshader.h"
#include <engine/rendering/renderingengine.h>

ForwardPointShader::ForwardPointShader(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint vertexArrayName, QObject *parent) :
	Shader(f, "forwardpoint", vertexArrayName, parent)
{}

/*void ForwardPointShader::updateUniforms(Transform &transform, Material &material, RenderingEngine &renderingEngine)
{
	Camera &camera = renderingEngine.mainCamera();

	Matrix4f worldMatrix = transform.transformation();
	Matrix4f projectedMatrix = camera.calculateViewProjection() * worldMatrix;

	material.findTexture("diffuse")->bind();

	setUniform("model", worldMatrix);
	setUniform("modelViewProjection", projectedMatrix);

	setUniformf("specularIntensity", material.findFloat("specularIntensity"));
	setUniformf("specularPower", material.findFloat("specularPower"));

	setUniform("C_eyePosition", camera.transform().calculateTransformedTranslation());

	setUniform("pointLight", static_cast<PointLight &>(*renderingEngine.activeLight()));
}

void ForwardPointShader::setUniform(const QString &uniformName, const BaseLight &baseLight)
{
	setUniform(uniformName + ".color", baseLight.color());
	setUniformf(uniformName + ".intensity", baseLight.intensity());
}*/
