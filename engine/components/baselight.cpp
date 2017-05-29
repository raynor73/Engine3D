#include <engine/components/baselight.h>
#include <engine/rendering/renderingengine.h>

BaseLight::BaseLight(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine, const Vector3f &color,
					 float intensity, QObject *parent) :
	GameComponent(parent),
	f(f),
	m_renderingEngine(renderingEngine),
	m_color(color),
	m_intensity(intensity)
{}

void BaseLight::addToRenderingEngine(RenderingEngine &)
{
	m_renderingEngine.addLight(this);
}
