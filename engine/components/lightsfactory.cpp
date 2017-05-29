#include "lightsfactory.h"
#include <engine/rendering/renderingengine.h>

QSharedPointer<DirectionalLight> LightsFactory::createDirectionalLight(QOPENGLFUNCTIONS_CLASSNAME &f,
																	 RenderingEngine &renderingEngine,
																	 const Vector3f &color, float intensity)
{
	QSharedPointer<Shader> shader =
			QSharedPointer<Shader>::create(f, "forwarddirectional", renderingEngine.vertexArrayName());
	return QSharedPointer<DirectionalLight>::create(f, renderingEngine, color, intensity, shader);
}

QSharedPointer<PointLight> LightsFactory::createPointLight(QOPENGLFUNCTIONS_CLASSNAME &f,
											RenderingEngine &renderingEngine,
											const Vector3f &color, float intensity,
											const Attenuation &attenuation)
{
	QSharedPointer<Shader> shader =
			QSharedPointer<Shader>::create(f, "forwardpoint", renderingEngine.vertexArrayName());
	return QSharedPointer<PointLight>::create(f, renderingEngine, color, intensity, attenuation, shader);
}

QSharedPointer<SpotLight> LightsFactory::createSpotLight(QOPENGLFUNCTIONS_CLASSNAME &f,
										  RenderingEngine &renderingEngine,
										  const Vector3f &color, float intensity,
										  const Attenuation &attenuation, float cutoff)
{
	QSharedPointer<Shader> shader =
			QSharedPointer<Shader>::create(f, "forwardspot", renderingEngine.vertexArrayName());
	return QSharedPointer<SpotLight>::create(f, renderingEngine, color, intensity, attenuation, cutoff, shader);
}
