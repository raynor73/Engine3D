#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include <graphics/shader.h>
#include <geometry/vector3f.h>
#include "qopenglfunctions_selector.h"

class PhongShader : public Shader
{
public:
	PhongShader(QOPENGLFUNCTIONS_CLASSNAME &, QObject *parent = 0);

	virtual void updateUniforms(const Matrix4f &, const Matrix4f &, const Material &);

	Vector3f ambientLight() const { return m_ambientLight; }
	void setAmbientLight(const Vector3f &ambientLight) { m_ambientLight = ambientLight; }

private:
	Vector3f m_ambientLight;
};

#endif // PHONGSHADER_H
