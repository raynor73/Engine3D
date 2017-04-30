#include "directionallight.h"
#include <engine/core/renderingengine.h>
#include <engine/rendering/forwarddirectionalshader.h>

DirectionalLight::DirectionalLight(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine,
								   const Vector3f &color, float intensity, const Vector3f &direction, QObject *parent) :
	BaseLight(f, renderingEngine, color, intensity, parent),
	m_direction(direction.normalized())
{
	m_shader = new ForwardDirectionalShader(f, m_renderingEngine);
}
