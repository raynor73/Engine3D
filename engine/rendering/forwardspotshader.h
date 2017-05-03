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
	ForwardSpotShader(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &, QObject *parent = 0);

	virtual void updateUniforms(const Transform &, Camera &, const Material &);
	using Shader::setUniform;
	void setUniform(const QString &, const BaseLight &);
	void setUniform(const QString &, PointLight &);
	void setUniform(const QString &, SpotLight &);
};

#endif // FORWARDSPOTSHADER_H
