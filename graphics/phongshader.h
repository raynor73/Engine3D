#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include <graphics/shader.h>
#include "qopenglfunctions_selector.h"

class PhongShader : public Shader
{
public:
	PhongShader(QOPENGLFUNCTIONS_CLASSNAME &, QObject *parent = 0);

	virtual void updateUniforms(const Matrix4f &, const Matrix4f &, const Material &);
};

#endif // PHONGSHADER_H
