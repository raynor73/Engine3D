#ifndef FORWARDPOINTSHADER_H
#define FORWARDPOINTSHADER_H

#include <engine/rendering/qopenglfunctions_selector.h>
#include <engine/rendering/shader.h>
#include <engine/components/baselight.h>
#include <engine/components/pointlight.h>

class RenderingEngine;
class ForwardPointShader : public Shader
{
	Q_OBJECT

public:
	ForwardPointShader(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint vertexArrayName, QObject *parent = 0);
};

#endif // FORWARDPOINTSHADER_H
