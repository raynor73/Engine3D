#include "renderutils.h"

void RenderUtils::clearScreen()
{
    // TODO: Stencil buffer
	//f.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
}

void RenderUtils::initGraphics()
{
	glClearColor(0, 0, 0, 0);

	/*f.glFrontFace(GL_CW);
    f.glCullFace(GL_BACK);
    f.glEnable(GL_CULL_FACE);
	f.glEnable(GL_DEPTH_TEST);*/

    // TODO: Depth clamp

	//f.glEnable(GL_FRAMEBUFFER_SRGB);

	/*f.glDisable(GL_TEXTURE);
	f.glDisable(GL_DEPTH_TEST);
	f.glDisable(GL_ALPHA_TEST);
	f.glDisable(GL_CULL_FACE);*/
}

QString RenderUtils::getOpenGLVersion()
{
	return QString::fromLocal8Bit(reinterpret_cast<const char *>(glGetString(GL_VERSION)));
}

GLint RenderUtils::glGetShader(GLuint shader, GLenum pname)
{
	GLint result;
	glGetShaderiv(shader, pname, &result);
	return result;
}

GLint RenderUtils::glGetProgram(GLuint program, GLenum pname)
{
	GLint result;
	glGetProgramiv(program, pname, &result);
	return result;
}
