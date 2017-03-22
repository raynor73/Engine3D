#include "renderutils.h"

void RenderUtils::clearScreen(QOpenGLFunctions &f)
{
    // TODO: Stencil buffer
    f.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderUtils::initGraphics(QOpenGLFunctions &f)
{
	f.glClearColor(0, 1, 1, 0);

    f.glFrontFace(GL_CW);
    f.glCullFace(GL_BACK);
    f.glEnable(GL_CULL_FACE);
    f.glEnable(GL_DEPTH_TEST);

    // TODO: Depth clamp

    f.glEnable(GL_FRAMEBUFFER_SRGB);
}

QString RenderUtils::getOpenGLVersion(QOpenGLFunctions &f)
{
	return QString::fromLocal8Bit(reinterpret_cast<const char *>(f.glGetString(GL_VERSION)));
}

GLint RenderUtils::glGetShader(QOpenGLFunctions &f, GLuint shader, GLenum pname)
{
	GLint result;
	f.glGetShaderiv(shader, pname, &result);
	return result;
}

GLint RenderUtils::glGetProgram(QOpenGLFunctions &f, GLuint program, GLenum pname)
{
	GLint result;
	f.glGetProgramiv(program, pname, &result);
	return result;
}
