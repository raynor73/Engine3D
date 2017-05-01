#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <QObject>
#include <engine/components/baselight.h>
#include <engine/components/attenuation.h>
#include <engine/core/vector3f.h>
#include <engine/rendering/qopenglfunctions_selector.h>

class RenderingEngine;
class QOPENGLFUNCTIONS_CLASSNAME;
class PointLight : public BaseLight
{
	Q_OBJECT
public:
	PointLight(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine, const Vector3f &color, float intensity,
			   const Attenuation &attenuation, const Vector3f &position, float range, QObject *parent = 0);

	Attenuation attenuation() const { return m_attenuation; }
	Vector3f position() const { return m_position; }
	float range() const { return m_range; }
	void setAttenuation(const Attenuation &attenuation) { m_attenuation = attenuation; }
	void setPosition(const Vector3f &position) { m_position = position; }
	void setRange(float range) { m_range = range; }

protected:
	Attenuation m_attenuation;
	Vector3f m_position;
	float m_range;
};

#endif // POINTLIGHT_H
