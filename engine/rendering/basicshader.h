#ifndef BASICSHADER_H
#define BASICSHADER_H

#include <engine/rendering/qopenglfunctions_selector.h>
#include <engine/rendering/shader.h>

class BasicShader : public Shader
{
	Q_OBJECT

public:
	BasicShader(QOPENGLFUNCTIONS_CLASSNAME &f, QObject *parent = 0);

	virtual void updateUniforms(const Matrix4f &, const Matrix4f &, const Material &);
};

#endif // BASICSHADER_H
