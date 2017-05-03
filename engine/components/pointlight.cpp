#include <engine/components/pointlight.h>
#include <engine/rendering/forwardpointshader.h>
#include <cmath>
#include <QDebug>

PointLight::PointLight(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine, const Vector3f &color,
					   float intensity, const Attenuation &attenuation, QObject *parent) :
	BaseLight(f, renderingEngine, color, intensity, parent),
	m_attenuation(attenuation)
{
	m_shader = new ForwardPointShader(f, m_renderingEngine);

	float a = m_attenuation.exponent();
	float b = m_attenuation.linear();
	float c = m_attenuation.constant() - COLOR_DEPTH * m_intensity * m_color.max();
	m_range = (-b + std::sqrt(b * b - 4 * a * c))/(2 * a);
}
