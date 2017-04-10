#include "spotlight.h"

SpotLight::SpotLight(const PointLight &pointLight, const Vector3f &direction, float cutoff, QObject *parent) :
	QObject(parent),
	m_pointLight(pointLight),
	m_direction(direction.normalized()),
	m_cutoff(cutoff)
{}

SpotLight::SpotLight(const SpotLight &other) :
	QObject(other.parent()),
	m_pointLight(other.m_pointLight),
	m_direction(other.m_direction),
	m_cutoff(other.m_cutoff)
{}

SpotLight &SpotLight::operator =(const SpotLight &other)
{
	if (&other == this)
		return *this;

	m_pointLight = other.m_pointLight;
	m_direction = other.m_direction;
	m_cutoff = other.m_cutoff;

	return *this;
}
