#include <engine/rendering/attenuation.h>

Attenuation::Attenuation(float constant, float linear, float exponent, QObject *parent) :
	QObject(parent),
	m_constant(constant),
	m_linear(linear),
	m_exponent(exponent)
{}

Attenuation::Attenuation(const Attenuation &other) :
	QObject(other.parent()),
	m_constant(other.m_constant),
	m_linear(other.m_linear),
	m_exponent(other.exponent())
{}

Attenuation &Attenuation::operator =(const Attenuation &other)
{
	if (&other == this)
		return *this;

	m_constant = other.m_constant;
	m_linear = other.m_linear;
	m_exponent = other.m_exponent;

	return *this;
}
