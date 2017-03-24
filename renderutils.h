#ifndef RENDERUTILS_H
#define RENDERUTILS_H

#include "qopenglfunctions_selector.h"
#include <QString>

namespace RenderUtils
{
void clearScreen(QOPENGLFUNCTIONS_CLASSNAME &);
void initGraphics(QOPENGLFUNCTIONS_CLASSNAME &);
QString getOpenGLVersion(QOPENGLFUNCTIONS_CLASSNAME &);
GLint glGetShader(QOPENGLFUNCTIONS_CLASSNAME &, GLuint, GLenum);
GLint glGetProgram(QOPENGLFUNCTIONS_CLASSNAME &, GLuint, GLenum);
QString glGetShaderInfoLog(QOPENGLFUNCTIONS_CLASSNAME &, GLuint);
}

#endif // RENDERUTILS_H
