#ifndef RENDERUTILS_H
#define RENDERUTILS_H

#include <QOpenGLFunctions_3_3_Core>
#include <QString>

namespace RenderUtils
{
void clearScreen(QOpenGLFunctions_3_3_Core &);
void initGraphics(QOpenGLFunctions_3_3_Core &);
QString getOpenGLVersion(QOpenGLFunctions_3_3_Core &);
GLint glGetShader(QOpenGLFunctions_3_3_Core &, GLuint, GLenum);
GLint glGetProgram(QOpenGLFunctions_3_3_Core &, GLuint, GLenum);
}

#endif // RENDERUTILS_H
