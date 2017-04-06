#include "pointlight.h"

PointLight::PointLight(const BaseLight &baseLight, const Attenuation &attenuation,
					   const Vector3f &position, QObject *parent) :
	QObject(parent),
	m_baseLight(baseLight),
	m_attenuation(attenuation),
	m_position(position)
{}

PointLight::PointLight(const PointLight &other) :
	QObject(other.parent()),
	m_baseLight(other.m_baseLight),
	m_attenuation(other.m_attenuation),
	m_position(other.m_position)
{}

PointLight &PointLight::operator =(const PointLight &other)
{
	if (&other == this)
		return *this;

	m_baseLight = other.m_baseLight;
	m_attenuation = other.m_attenuation;
	m_position = other.m_position;

	return *this;
}
