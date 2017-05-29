#include "directionallight.h"
#include <engine/rendering/renderingengine.h>

DirectionalLight::DirectionalLight(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine,
								   const Vector3f &color, float intensity, QSharedPointer<Shader> shader,
								   QObject *parent) :
	BaseLight(f, renderingEngine, color, intensity, parent)
{
	m_shader = shader;
}

Vector3f DirectionalLight::direction()
{
	return transform().calculateTransformedRotation().calculateForward().normalized();
}
