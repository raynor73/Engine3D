#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <QObject>
#include "baselight.h"
#include "attenuation.h"
#include <geometry/vector3f.h>

class PointLight : public QObject
{
	Q_OBJECT
public:
	PointLight(const BaseLight &, const Attenuation &, const Vector3f &, QObject *parent = 0);
	PointLight(const PointLight &);

	PointLight &operator =(const PointLight &);

	BaseLight baseLight() const { return m_baseLight; }
	Attenuation attenuation() const { return m_attenuation; }
	Vector3f position() const { return m_position; }
	void setBaseLight(const BaseLight baseLight) { m_baseLight = baseLight; }
	void setAttenuation(const Attenuation attenuation) { m_attenuation = attenuation; }
	void setPosition(const Vector3f position) { m_position = position; }

private:
	BaseLight m_baseLight;
	Attenuation m_attenuation;
	Vector3f m_position;
};

#endif // POINTLIGHT_H
