#ifndef RENDERUTILS_H
#define RENDERUTILS_H

#include <engine/rendering/qopenglfunctions_selector.h>
#include <QString>
#include <engine/core/vector3f.h>

namespace RenderUtils
{

void clearScreen(QOPENGLFUNCTIONS_CLASSNAME &);
void initGraphics(QOPENGLFUNCTIONS_CLASSNAME &);
QString getOpenGLVersion(QOPENGLFUNCTIONS_CLASSNAME &);
GLint glGetShader(QOPENGLFUNCTIONS_CLASSNAME &, GLuint, GLenum);
GLint glGetProgram(QOPENGLFUNCTIONS_CLASSNAME &, GLuint, GLenum);
QString glGetShaderInfoLog(QOPENGLFUNCTIONS_CLASSNAME &, GLuint);
void setClearColor(QOPENGLFUNCTIONS_CLASSNAME &, const Vector3f &);
void enableTextures(QOPENGLFUNCTIONS_CLASSNAME &, bool);
void unbindTextures(QOPENGLFUNCTIONS_CLASSNAME &);
void printUniforms(QOPENGLFUNCTIONS_CLASSNAME &, GLuint);

}

#endif // RENDERUTILS_H
