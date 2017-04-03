#include "phongshader.h"
#include <utils.h>
#include <renderutils.h>

PhongShader::PhongShader(QOPENGLFUNCTIONS_CLASSNAME &f, QObject *parent) :
	Shader(f, parent),
	m_ambientLight(Vector3f(1, 1, 1)),
	m_directionalLight(DirectionalLight(BaseLight(Vector3f(1, 1, 1), 0), Vector3f(0, 0, 0)))
{
	setVertexShader(Utils::loadShader("phongvertex.vsh"));
	setFragmentShader(Utils::loadShader("phongfragment.fsh"));
	linkProgram();

	addUniform("transform");
	addUniform("transformProjected");
	addUniform("baseColor");
	addUniform("ambientLight");

	addUniform("directionalLight.base.color");
	addUniform("directionalLight.base.intensity");
	addUniform("directionalLight.direction");
}

void PhongShader::updateUniforms(const Matrix4f &worldMatrix, const Matrix4f &projectedMatrix, const Material &material)
{
	if (material.texture() != NULL)
		material.texture()->bind();
	else
		RenderUtils::unbindTextures(f);

	setUniform("transformProjected", projectedMatrix);
	setUniform("transform", worldMatrix);
	setUniform("baseColor", material.color());
	setUniform("ambientLight", m_ambientLight);
	setUniform("directionalLight", m_directionalLight);
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
