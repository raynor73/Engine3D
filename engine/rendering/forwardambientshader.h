#ifndef FORWARDAMBIENTSHADER_H
#define FORWARDAMBIENTSHADER_H

#include <engine/rendering/qopenglfunctions_selector.h>
#include <engine/rendering/shader.h>

class RenderingEngine;
class ForwardAmbientShader : public Shader
{
	Q_OBJECT

public:
	ForwardAmbientShader(QOPENGLFUNCTIONS_CLASSNAME &f, const RenderingEngine &, QObject *parent = 0);

	virtual void updateUniforms(const Transform &, Camera &, const Material &);
};

#endif // FORWARDAMBIENTSHADER_H
