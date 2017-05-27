#ifndef FORWARDSPOTSHADER_H
#define FORWARDSPOTSHADER_H

#include <engine/rendering/qopenglfunctions_selector.h>
#include <engine/rendering/shader.h>
#include <engine/components/baselight.h>
#include <engine/components/pointlight.h>
#include <engine/components/spotlight.h>

class RenderingEngine;
class ForwardSpotShader : public Shader
{
	Q_OBJECT

public:
	ForwardSpotShader(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint vertexArrayName, QObject *parent = 0);
};

#endif // FORWARDSPOTSHADER_H
