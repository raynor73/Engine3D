#ifndef ATTENUATION_H
#define ATTENUATION_H

#include <engine/core/vector3f.h>

class Attenuation : public Vector3f
{
	Q_OBJECT
public:
	Attenuation(float constant, float linear, float exponent, QObject *parent = 0);

	float constant() const { return x; }
	float linear() const { return y; }
	float exponent() const { return z; }
	void setConstant(float constant) { x = constant; }
	void setLinear(float linear) { y = linear; }
	void setExponent(float exponent) { z = exponent; }
};

#endif // ATTENUATION_H
