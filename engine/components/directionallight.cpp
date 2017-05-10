#include "directionallight.h"
#include <engine/rendering/renderingengine.h>
#include <engine/rendering/forwarddirectionalshader.h>

DirectionalLight::DirectionalLight(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine,
								   const Vector3f &color, float intensity, QObject *parent) :
	BaseLight(f, renderingEngine, color, intensity, parent)
{
	m_shader = new ForwardDirectionalShader(f, m_renderingEngine);
}

Vector3f DirectionalLight::direction()
{
	return transform().rotation().calculateForward().normalized();
}
