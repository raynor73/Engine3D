#include "shaderresource.h"

ShaderResource::ShaderResource()
{
	m_programReference = _glCreateProgram();
	Q_ASSERT(m_programReference != 0);
}

ShaderResource::~ShaderResource()
{
	_glDeleteProgram(m_programReference);
}
