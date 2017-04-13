#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <QObject>
#include <engine/core/vector3f.h>
#include <engine/rendering/baselight.h>

class DirectionalLight : public QObject
{
	Q_OBJECT
public:
	DirectionalLight(const BaseLight &, const Vector3f &, QObject *parent = 0);
	DirectionalLight(const DirectionalLight &);

	BaseLight base() const { return m_base; }
	Vector3f direction() const { return m_direction;}
	void setBase(const BaseLight &base) { m_base = base; }
	void setDirection(const Vector3f &direction) { m_direction = direction.normalized(); }

	DirectionalLight &operator =(const DirectionalLight &);

private:
	BaseLight m_base;
	Vector3f m_direction;
};

#endif // DIRECTIONALLIGHT_H
