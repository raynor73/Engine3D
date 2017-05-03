#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <QObject>
#include <engine/components/pointlight.h>
#include <engine/rendering/qopenglfunctions_selector.h>
#include <engine/core/vector3f.h>

class QOPENGLFUNCTIONS_CLASSNAME;
class RenderingEngine;
class Attenuation;
class SpotLight : public PointLight
{
	Q_OBJECT
public:
	SpotLight(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine, const Vector3f &color, float intensity,
			  const Attenuation &attenuation, const Vector3f &direction, float cutoff, QObject *parent = 0);

	Vector3f direction() const { return m_direction; }
	float cutoff() const { return m_cutoff; }
	void setDirection(const Vector3f &direction) { m_direction = direction.normalized(); }
	void setCutoff(float cutoff) { m_cutoff = cutoff; }

protected:
	Vector3f m_direction;
	float m_cutoff;
};

#endif // SPOTLIGHT_H
