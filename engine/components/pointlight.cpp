#include <engine/components/pointlight.h>
#include <engine/rendering/forwardpointshader.h>

PointLight::PointLight(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine, const Vector3f &color,
					   float intensity, const Attenuation &attenuation, const Vector3f &position, float range,
					   QObject *parent) :
	BaseLight(f, renderingEngine, color, intensity, parent),
	m_attenuation(attenuation),
	m_position(position),
	m_range(range)
{
	m_shader = new ForwardPointShader(f, m_renderingEngine);
}
