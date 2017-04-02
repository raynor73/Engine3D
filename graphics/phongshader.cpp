#include "phongshader.h"
#include <utils.h>
#include <renderutils.h>

PhongShader::PhongShader(QOPENGLFUNCTIONS_CLASSNAME &f, QObject *parent) : Shader(f, parent)
{
	setVertexShader(Utils::loadShader("phongvertex.vsh"));
	setFragmentShader(Utils::loadShader("phongfragment.fsh"));
	linkProgram();

	addUniform("transform");
	addUniform("color");
}

void PhongShader::updateUniforms(const Matrix4f &, const Matrix4f &projectedMatrix, const Material &material)
{
	if (material.texture() != NULL)
		material.texture()->bind();
	else
		RenderUtils::unbindTextures(f);

	setUniform("transform", projectedMatrix);
	setUniform("color", material.color());
}
