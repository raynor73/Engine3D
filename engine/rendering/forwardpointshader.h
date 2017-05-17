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

	virtual void updateUniforms(Transform &, Material &, RenderingEngine &) override;
	using Shader::setUniform;
	void setUniform(const QString &, const BaseLight &);
	void setUniform(const QString &, PointLight &);
};

#endif // FORWARDPOINTSHADER_H
