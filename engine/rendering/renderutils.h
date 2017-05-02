#ifndef RENDERUTILS_H
#define RENDERUTILS_H

#include <engine/rendering/qopenglfunctions_selector.h>
#include <QString>
#include <engine/core/vector3f.h>

namespace RenderUtils
{

GLint glGetShader(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint shader, GLenum pname);
GLint glGetProgram(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint program, GLenum pname);
QString glGetProgramInfoLog(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint program);
QString glGetShaderInfoLog(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint shaderReference);
void printUniforms(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint program);

}

#endif // RENDERUTILS_H
