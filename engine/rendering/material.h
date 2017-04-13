#ifndef MATERIAL_H
#define MATERIAL_H

#include <QObject>
#include <engine/core/vector3f.h>
#include "texture.h"

class Material : public QObject
{
	Q_OBJECT

public:
	Material(Texture *, const Vector3f &, QObject *parent = 0);
	Material(const Vector3f &, QObject *parent = 0);
	Material(const Vector3f &, float, float, QObject *parent = 0);
	Material(Texture *, const Vector3f &, float, float, QObject *parent = 0);
	~Material();

	Texture *texture() const { return m_texture; }
	Vector3f color() const { return m_color; }
	float specularIntensity() const { return m_specularIntensity; }
	float specularPower() const { return m_specularPower; }
	void setTexture(Texture *);
	void setColor(const Vector3f &);
	void setSpecularIntensity(float specularIntensity) { m_specularIntensity = specularIntensity; }
	void setSpecularPower(float specularExponent) { m_specularPower = specularExponent; }

private:
	Texture *m_texture;
	Vector3f m_color;
	float m_specularIntensity;
	float m_specularPower;
};

#endif // MATERIAL_H
