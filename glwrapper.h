#ifndef GLWRAPPER_H
#define GLWRAPPER_H

#include <engine/rendering/qopenglfunctions_selector.h>

void setOpenGLFunctions(QOPENGLFUNCTIONS_CLASSNAME *);

void _glGenBuffers(GLsizei n, GLuint * buffers);
void _glDeleteBuffers(GLsizei n, GLuint *buffers);

#endif // GLWRAPPER_H
