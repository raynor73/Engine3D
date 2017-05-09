#ifndef BASICSHADER_H
#define BASICSHADER_H

#include <engine/rendering/qopenglfunctions_selector.h>
#include <engine/rendering/shader.h>

class RenderingEngine;
class BasicShader : public Shader
{
	Q_OBJECT

public:
	BasicShader(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &, QObject *parent = 0);

	virtual void updateUniforms(Transform &, Camera &, const Material &) override;
};

#endif // BASICSHADER_H
