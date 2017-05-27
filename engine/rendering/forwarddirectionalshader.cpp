#include "forwarddirectionalshader.h"
#include <engine/rendering/renderingengine.h>

ForwardDirectionalShader::ForwardDirectionalShader(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint vertexArrayName,
												   QObject *parent) :
	Shader(f, "forwarddirectional", vertexArrayName, parent)
{}
