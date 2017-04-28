#include "directionallight.h"
#include <engine/core/renderingengine.h>

DirectionalLight::DirectionalLight(const BaseLight &base, const Vector3f &direction, QObject *parent) :
	GameComponent(parent),
	m_base(base),
	m_direction(direction.normalized())
{}

DirectionalLight::DirectionalLight(const DirectionalLight &other) :
	GameComponent(other.parent()),
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

void DirectionalLight::addToRenderingEngine(RenderingEngine &renderingENgine)
{
	// TODO Don't forget to implement removing
	renderingENgine.addDirectionalLight(this);
}
