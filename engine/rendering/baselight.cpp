#include "baselight.h"

BaseLight::BaseLight(const Vector3f &color, float intensity, QObject *parent) :
	QObject(parent),
	m_color(color),
	m_intensity(intensity)
{}

BaseLight::BaseLight(const BaseLight &other) :
	QObject(other.parent()),
	m_color(other.m_color),
	m_intensity(other.m_intensity)
{}

BaseLight &BaseLight::operator =(const BaseLight &other)
{
	if (&other == this)
		return *this;

	m_color = other.m_color;
	m_intensity = other.m_intensity;

	return *this;
}
