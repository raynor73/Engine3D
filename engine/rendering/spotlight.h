#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <QObject>
#include <engine/components/pointlight.h>
#include <engine/core/vector3f.h>

class SpotLight : public QObject
{
	Q_OBJECT
public:
	SpotLight(const PointLight &, const Vector3f &, float, QObject *parent = 0);
	SpotLight(const SpotLight &);

	SpotLight &operator =(const SpotLight &);

	PointLight &pointLight() { return m_pointLight; }
	Vector3f direction() const { return m_direction; }
	float cutoff() const { return m_cutoff; }
	void setPointLight(const PointLight &pointLight) { m_pointLight = pointLight; }
	void setDirection(const Vector3f &direction) { m_direction = direction.normalized(); }
	void setCutoff(float cutoff) { m_cutoff = cutoff; }

private:
	PointLight m_pointLight;
	Vector3f m_direction;
	float m_cutoff;
};

#endif // SPOTLIGHT_H
