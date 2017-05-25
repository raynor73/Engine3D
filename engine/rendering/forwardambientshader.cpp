#include "forwardambientshader.h"
#include <engine/rendering/renderingengine.h>

ForwardAmbientShader::ForwardAmbientShader(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint vertexArrayName, QObject *parent) :
	Shader(f, "forwardambient", vertexArrayName, parent)
{}

void ForwardAmbientShader::updateUniforms(Transform &transform, Material &material, RenderingEngine &renderingEngine)
{
	/*Matrix4f worldMatrix = transform.transformation();
	Matrix4f projectedMatrix = renderingEngine.mainCamera().calculateViewProjection() * worldMatrix;*/

	Shader::updateUniforms(transform, material, renderingEngine);

	material.findTexture("diffuse")->bind();

	//setUniform("T_modelViewProjection", projectedMatrix);
	setUniform("R_ambient", renderingEngine.ambientLight());
}
