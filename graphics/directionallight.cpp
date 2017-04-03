#include "directionallight.h"

DirectionalLight::DirectionalLight(const BaseLight &base, const Vector3f &direction, QObject *parent) :
	QObject(parent),
	m_base(base),
	m_direction(direction)
{}

DirectionalLight::DirectionalLight(const DirectionalLight &other) :
	QObject(other.parent()),
	m_base(other.m_base),
	m_direction(other.m_direction)
{}

DirectionalLight &DirectionalLight::operator =(const DirectionalLight &other)
{
	if (&other == this)
		return *this;

	m_base = other.m_base;
	m_direction = other.m_direction;

	return *this;
}
