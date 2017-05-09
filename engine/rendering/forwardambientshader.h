#ifndef FORWARDAMBIENTSHADER_H
#define FORWARDAMBIENTSHADER_H

#include <engine/rendering/qopenglfunctions_selector.h>
#include <engine/rendering/shader.h>

class RenderingEngine;
class ForwardAmbientShader : public Shader
{
	Q_OBJECT

public:
	ForwardAmbientShader(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &, QObject *parent = 0);

	virtual void updateUniforms(Transform &, Camera &, const Material &) override;
};

#endif // FORWARDAMBIENTSHADER_H
