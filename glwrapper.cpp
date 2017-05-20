#include "glwrapper.h"

static QOPENGLFUNCTIONS_CLASSNAME *f;

void setOpenGLFunctions(QOPENGLFUNCTIONS_CLASSNAME *openglFunctions)
{
	f = openglFunctions;
}

void glGenBuffers(GLsizei n, GLuint *buffers)
{
	f->glGenBuffers(n ,buffers);
}

void glDeleteBuffers(GLsizei n, GLuint *buffers)
{
	f->glDeleteBuffers(n, buffers);
}

