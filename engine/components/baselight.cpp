#include <engine/components/baselight.h>
#include <engine/core/renderingengine.h>

BaseLight::BaseLight(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine, const Vector3f &color,
					 float intensity, QObject *parent) :
	GameComponent(parent),
	f(f),
	m_renderingEngine(renderingEngine),
	m_color(color),
	m_intensity(intensity),
	m_shader(NULL)
{}

BaseLight::~BaseLight()
{
	if (m_shader != NULL)
		delete m_shader;
}

void BaseLight::addToRenderingEngine()
{
	m_renderingEngine.addLight(this);
}
