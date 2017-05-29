#include <engine/components/spotlight.h>
#include <engine/components/attenuation.h>
#include <engine/rendering/renderingengine.h>

SpotLight::SpotLight(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine, const Vector3f &color,
					 float intensity, const Attenuation &attenuation, float cutoff, QSharedPointer<Shader> shader,
					 QObject *parent) :
	PointLight(f, renderingEngine, color, intensity, attenuation, shader, parent),
	m_cutoff(cutoff)
{}

Vector3f SpotLight:: direction()
{
	return transform().calculateTransformedRotation().calculateForward();
}
