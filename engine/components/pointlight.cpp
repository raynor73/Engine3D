#include <engine/components/pointlight.h>
#include <engine/core/renderingengine.h>

PointLight::PointLight(const BaseLight &baseLight, const Attenuation &attenuation,
					   const Vector3f &position, float range, QObject *parent) :
	GameComponent(parent),
	m_baseLight(baseLight),
	m_attenuation(attenuation),
	m_position(position),
	m_range(range)
{}

PointLight::PointLight(const PointLight &other) :
	GameComponent(other.parent()),
	m_baseLight(other.m_baseLight),
	m_attenuation(other.m_attenuation),
	m_position(other.m_position),
	m_range(other.m_range)
{}

PointLight &PointLight::operator =(const PointLight &other)
{
	if (&other == this)
		return *this;

	m_baseLight = other.m_baseLight;
	m_attenuation = other.m_attenuation;
	m_position = other.m_position;
	m_range = other.m_range;

	return *this;
}

void PointLight::addToRenderingEngine(RenderingEngine &renderingEngine)
{
	// TODO Don't forget to implement removing
	renderingEngine.addPointLight(this);
}
