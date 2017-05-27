#ifndef FORWARDDIRECTIONALSHADER_H
#define FORWARDDIRECTIONALSHADER_H

#include <engine/rendering/qopenglfunctions_selector.h>
#include <engine/rendering/shader.h>
#include <engine/components/baselight.h>
#include <engine/components/directionallight.h>

class RenderingEngine;
class ForwardDirectionalShader : public Shader
{
	Q_OBJECT

public:
	ForwardDirectionalShader(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint vertexArrayName, QObject *parent = 0);
};

#endif // FORWARDDIRECTIONALSHADER_H
