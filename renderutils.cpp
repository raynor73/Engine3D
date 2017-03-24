#include "renderutils.h"

void RenderUtils::clearScreen(QOpenGLFunctions_3_3_Core &f)
{
    // TODO: Stencil buffer
	//f.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	f.glClear(GL_COLOR_BUFFER_BIT);
}

void RenderUtils::initGraphics(QOpenGLFunctions_3_3_Core &f)
{
	f.glClearColor(0, 0, 0, 0);

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

QString RenderUtils::getOpenGLVersion(QOpenGLFunctions_3_3_Core &f)
{
	return QString::fromLocal8Bit(reinterpret_cast<const char *>(f.glGetString(GL_VERSION)));
}

GLint RenderUtils::glGetShader(QOpenGLFunctions_3_3_Core &f, GLuint shader, GLenum pname)
{
	GLint result;
	f.glGetShaderiv(shader, pname, &result);
	return result;
}

GLint RenderUtils::glGetProgram(QOpenGLFunctions_3_3_Core &f, GLuint program, GLenum pname)
{
	GLint result;
	f.glGetProgramiv(program, pname, &result);
	return result;
}
