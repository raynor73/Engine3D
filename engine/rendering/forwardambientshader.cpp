#include "forwardambientshader.h"
#include <engine/rendering/renderingengine.h>

ForwardAmbientShader::ForwardAmbientShader(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint vertexArrayName, QObject *parent) :
	Shader(f, "forwardambient", vertexArrayName, parent)
{}
