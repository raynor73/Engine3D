#include "forwardambientshader.h"
#include <engine/rendering/renderingengine.h>

ForwardAmbientShader::ForwardAmbientShader(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine,
										   QObject *parent) :
	Shader(f, renderingEngine, parent)
{
	setVertexShaderFromFile("forwardambient.vsh");
	setFragmentShaderFromFile("forwardambient.fsh");
	linkProgram();

	addUniform("modelViewProjection");
	addUniform("ambientIntensity");
}

void ForwardAmbientShader::updateUniforms(Transform &transform, Camera &camera, const Material &material)
{
	Matrix4f worldMatrix = transform.transformation();
	Matrix4f projectedMatrix = camera.calculateViewProjection() * worldMatrix;

	material.texture()->bind();

	setUniform("modelViewProjection", projectedMatrix);
	setUniform("ambientIntensity", m_renderingEngine.ambientLight());
}
