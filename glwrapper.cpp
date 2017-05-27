#include "glwrapper.h"

static QOPENGLFUNCTIONS_CLASSNAME *f;

void setOpenGLFunctions(QOPENGLFUNCTIONS_CLASSNAME *openglFunctions)
{
	f = openglFunctions;
}

GLuint _glCreateProgram(void)
{
	return f->glCreateProgram();
}

void _glDeleteProgram(GLuint program)
{
	f->glDeleteProgram(program);
}

void _glGenBuffers(GLsizei n, GLuint *buffers)
{
	f->glGenBuffers(n ,buffers);
}

void _glDeleteBuffers(GLsizei n, GLuint *buffers)
{
	f->glDeleteBuffers(n, buffers);
}

void _glActiveTexture(GLenum texture)
{
	f->glActiveTexture(texture);
}
