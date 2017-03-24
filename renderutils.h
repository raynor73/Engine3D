#ifndef RENDERUTILS_H
#define RENDERUTILS_H

#include <QString>
#include <GL/glew.h>

namespace RenderUtils
{
void clearScreen();
void initGraphics();
QString getOpenGLVersion();
GLint glGetShader(GLuint, GLenum);
GLint glGetProgram(GLuint, GLenum);
}

#endif // RENDERUTILS_H
