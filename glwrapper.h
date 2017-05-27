#ifndef GLWRAPPER_H
#define GLWRAPPER_H

#include <engine/rendering/qopenglfunctions_selector.h>

void setOpenGLFunctions(QOPENGLFUNCTIONS_CLASSNAME *);

GLuint _glCreateProgram(void);
void _glDeleteProgram(GLuint program);
void _glGenBuffers(GLsizei n, GLuint * buffers);
void _glDeleteBuffers(GLsizei n, GLuint *buffers);
void _glActiveTexture(GLenum texture);

#endif // GLWRAPPER_H
