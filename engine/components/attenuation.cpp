#include <engine/components/attenuation.h>

Attenuation::Attenuation(float constant, float linear, float exponent, QObject *parent) :
	Vector3f(constant, linear, exponent, parent)
{}
