#ifndef RENDERUTILS_H
#define RENDERUTILS_H

#include <QOpenGLFunctions>
#include <QString>

namespace RenderUtils
{
void clearScreen(QOpenGLFunctions &);
void initGraphics(QOpenGLFunctions &);
QString getOpenGLVersion(QOpenGLFunctions &);
GLint glGetShader(QOpenGLFunctions &, GLuint, GLenum);
}

#endif // RENDERUTILS_H
