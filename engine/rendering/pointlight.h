#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <QObject>
#include "baselight.h"
#include "attenuation.h"
#include <engine/core/vector3f.h>

class PointLight : public QObject
{
	Q_OBJECT
public:
	PointLight(const BaseLight &, const Attenuation &, const Vector3f &, float,
			   QObject *parent = 0);
	PointLight(const PointLight &);

	PointLight &operator =(const PointLight &);

	BaseLight baseLight() const { return m_baseLight; }
	Attenuation attenuation() const { return m_attenuation; }
	Vector3f position() const { return m_position; }
	float range() const { return m_range; }
	void setBaseLight(const BaseLight baseLight) { m_baseLight = baseLight; }
	void setAttenuation(const Attenuation attenuation) { m_attenuation = attenuation; }
	void setPosition(const Vector3f position) { m_position = position; }
	void setRange(float range) { m_range = range; }

private:
	BaseLight m_baseLight;
	Attenuation m_attenuation;
	Vector3f m_position;
	float m_range;
};

#endif // POINTLIGHT_H
