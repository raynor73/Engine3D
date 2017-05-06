#include <engine/components/spotlight.h>
#include <engine/components/attenuation.h>
#include <engine/rendering/renderingengine.h>
#include <engine/rendering/forwardspotshader.h>

SpotLight::SpotLight(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine, const Vector3f &color,
					 float intensity, const Attenuation &attenuation, float cutoff, QObject *parent) :
	PointLight(f, renderingEngine, color, intensity, attenuation, parent),
	m_cutoff(cutoff)
{
	m_shader = new ForwardSpotShader(f, m_renderingEngine);
}

Vector3f SpotLight:: direction()
{
	return transform().rotation().calculateForward();
}
