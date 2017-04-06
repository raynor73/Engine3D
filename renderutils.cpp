#include "renderutils.h"

void RenderUtils::clearScreen(QOPENGLFUNCTIONS_CLASSNAME &f)
{
	// TODO: Stencil buffer
	f.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderUtils::setClearColor(QOPENGLFUNCTIONS_CLASSNAME &f,const Vector3f &color)
{
	f.glClearColor(color.x, color.y, color.z, 1);
}

void RenderUtils::initGraphics(QOPENGLFUNCTIONS_CLASSNAME &f)
{
	f.glClearColor(0, 0, 0, 0);

	f.glFrontFace(GL_CW);
	f.glCullFace(GL_BACK);
	f.glEnable(GL_CULL_FACE);
	f.glEnable(GL_DEPTH_TEST);
	f.glEnable(GL_DEPTH_CLAMP);
	f.glEnable(GL_TEXTURE_2D);

	GLuint vertexArrayName;
	f.glGenVertexArrays(1, &vertexArrayName);
	f.glBindVertexArray(vertexArrayName);
}

void RenderUtils::enableTextures(QOPENGLFUNCTIONS_CLASSNAME &f, bool isEnabled)
{
	if (isEnabled)
		f.glEnable(GL_TEXTURE_2D);
	else
		f.glDisable(GL_TEXTURE_2D);
}

QString RenderUtils::getOpenGLVersion(QOPENGLFUNCTIONS_CLASSNAME &f)
{
	return QString::fromLocal8Bit(reinterpret_cast<const char *>(f.glGetString(GL_VERSION)));
}

GLint RenderUtils::glGetShader(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint shader, GLenum pname)
{
	GLint result;
	f.glGetShaderiv(shader, pname, &result);
	return result;
}

GLint RenderUtils::glGetProgram(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint program, GLenum pname)
{
	GLint result;
	f.glGetProgramiv(program, pname, &result);
	return result;
}

QString RenderUtils::glGetShaderInfoLog(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint shaderReference)
{
	char buffer[1024];
	GLsizei length;

	f.glGetShaderInfoLog(shaderReference, 1024, &length, buffer);

	return QString::fromLocal8Bit(buffer);
}

void RenderUtils::unbindTextures(QOPENGLFUNCTIONS_CLASSNAME &f)
{
	f.glBindTexture(GL_TEXTURE_2D, 0);
}

