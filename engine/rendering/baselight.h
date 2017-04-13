#ifndef BASELIGHT_H
#define BASELIGHT_H

#include <QObject>
#include <engine/core/vector3f.h>

class BaseLight : public QObject
{
	Q_OBJECT
public:
	BaseLight(const Vector3f &, float, QObject *parent = 0);
	BaseLight(const BaseLight &);


	Vector3f color() const { return m_color; }
	float intensity() const { return m_intensity; }
	void setColor(const Vector3f &color) { m_color = color; }
	void setIntensity(float intensity) { m_intensity = intensity; }

	BaseLight &operator =(const BaseLight &);

private:
	Vector3f m_color;
	float m_intensity;
};

#endif // BASELIGHT_H
