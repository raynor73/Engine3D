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
	ForwardDirectionalShader(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &, QObject *parent = 0);

	virtual void updateUniforms(const Transform &, Camera &, const Material &);
	using Shader::setUniform;
	void setUniform(const QString &, const BaseLight &);
	void setUniform(const QString &, const DirectionalLight &);
};

#endif // FORWARDDIRECTIONALSHADER_H
