#include <engine/components/baselight.h>
#include <engine/rendering/renderingengine.h>
#include <engine/core/coreengine.h>

BaseLight::BaseLight(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine, const Vector3f &color,
					 float intensity, QObject *parent) :
	GameComponent(parent),
	f(f),
	m_renderingEngine(renderingEngine),
	m_color(color),
	m_intensity(intensity)
{}

void BaseLight::addToEngine(CoreEngine &engine)
{
	engine.renderingEngine().addLight(this);
	//m_renderingEngine.addLight(this);
}
