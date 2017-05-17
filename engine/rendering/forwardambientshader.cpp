#include "forwardambientshader.h"
#include <engine/rendering/renderingengine.h>

ForwardAmbientShader::ForwardAmbientShader(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint vertexArrayName, QObject *parent) :
	Shader(f, vertexArrayName, parent)
{
	setVertexShaderFromFile("forwardambient.vsh");
	setFragmentShaderFromFile("forwardambient.fsh");
	linkProgram();

	addUniform("modelViewProjection");
	addUniform("ambientIntensity");
}

void ForwardAmbientShader::updateUniforms(Transform &transform, Material &material, RenderingEngine &renderingEngine)
{
	Matrix4f worldMatrix = transform.transformation();
	Matrix4f projectedMatrix = renderingEngine.mainCamera().calculateViewProjection() * worldMatrix;

	material.findTexture("diffuse")->bind();

	setUniform("modelViewProjection", projectedMatrix);
	setUniform("ambientIntensity", renderingEngine.ambientLight());
}
