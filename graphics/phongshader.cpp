#include "phongshader.h"
#include <utils.h>
#include <renderutils.h>

PhongShader::PhongShader(QOPENGLFUNCTIONS_CLASSNAME &f, QObject *parent) :
	Shader(f, parent),
	m_ambientLight(Vector3f(1, 1, 1))
{
	setVertexShader(Utils::loadShader("phongvertex.vsh"));
	setFragmentShader(Utils::loadShader("phongfragment.fsh"));
	linkProgram();

	addUniform("transform");
	addUniform("baseColor");
	addUniform("ambientLight");
}

void PhongShader::updateUniforms(const Matrix4f &, const Matrix4f &projectedMatrix, const Material &material)
{
	if (material.texture() != NULL)
		material.texture()->bind();
	else
		RenderUtils::unbindTextures(f);

	setUniform("transform", projectedMatrix);
	setUniform("baseColor", material.color());
	setUniform("ambientLight", m_ambientLight);
}
