#include "spotlight.h"
#include <engine/rendering/attenuation.h>
#include <engine/core/renderingengine.h>
#include <engine/rendering/forwardspotshader.h>

SpotLight::SpotLight(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine, const Vector3f &color,
					 float intensity, const Attenuation &attenuation, const Vector3f &position, float range,
					 const Vector3f &direction, float cutoff, QObject *parent) :
	PointLight(f, renderingEngine, color, intensity, attenuation, position, range, parent),
	m_direction(direction.normalized()),
	m_cutoff(cutoff)
{
	m_shader = new ForwardSpotShader(f, m_renderingEngine);
}
