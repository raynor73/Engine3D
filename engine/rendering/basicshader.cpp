#include "basicshader.h"
#include <engine/rendering/renderutils.h>

BasicShader::BasicShader(QOPENGLFUNCTIONS_CLASSNAME &f, QObject *parent) : Shader(f, parent)
{
	setVertexShaderFromFile("basicvertex.vsh");
	setFragmentShaderFromFile("basicfragment.fsh");
	linkProgram();

	addUniform("transform");
	addUniform("color");
}

void BasicShader::updateUniforms(const Transform &transform, Camera &camera, const Material &material)
{
	Matrix4f worldMatrix = transform.transformation();
	Matrix4f projectedMatrix = camera.calculateViewProjection() * worldMatrix;

	material.texture()->bind();

	setUniform("transform", projectedMatrix);
	setUniform("color", material.color());
}
