#include "basicshader.h"
#include <renderutils.h>

BasicShader::BasicShader(QOPENGLFUNCTIONS_CLASSNAME &f, QObject *parent) : Shader(f, parent)
{
	setVertexShaderFromFile("basicvertex.vsh");
	setFragmentShaderFromFile("basicfragment.fsh");
	linkProgram();

	addUniform("transform");
	addUniform("color");
}

void BasicShader::updateUniforms(const Matrix4f &, const Matrix4f &projectedMatrix, const Material &material)
{
	if (material.texture() != NULL)
		material.texture()->bind();
	else
		RenderUtils::unbindTextures(f);

	setUniform("transform", projectedMatrix);
	setUniform("color", material.color());
}
