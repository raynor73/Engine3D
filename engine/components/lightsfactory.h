#ifndef LIGHTSFACTORY_H
#define LIGHTSFACTORY_H

#include <QSharedPointer>
#include <engine/components/directionallight.h>
#include <engine/components/pointlight.h>
#include <engine/components/spotlight.h>
#include <engine/rendering/qopenglfunctions_selector.h>

class RenderingEngine;
class Vector3f;
class LightsFactory
{
public:
	static QSharedPointer<DirectionalLight> createDirectionalLight(QOPENGLFUNCTIONS_CLASSNAME &f,
																  RenderingEngine &renderingEngien,
																  const Vector3f &color, float intensity);
	static QSharedPointer<PointLight> createPointLight(QOPENGLFUNCTIONS_CLASSNAME &f,
													   RenderingEngine &renderingEngien,
													   const Vector3f &color, float intensity,
													   const Attenuation &attenuation);
	static QSharedPointer<SpotLight> createSpotLight(QOPENGLFUNCTIONS_CLASSNAME &f,
													 RenderingEngine &renderingEngien,
													 const Vector3f &color, float intensity,
													 const Attenuation &attenuation, float cutoff);
};

#endif // LIGHTSFACTORY_H
