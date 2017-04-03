#ifndef MATERIAL_H
#define MATERIAL_H

#include <QObject>
#include <geometry/vector3f.h>
#include "texture.h"

class Material : public QObject
{
	Q_OBJECT

public:
	Material(const Texture *, const Vector3f &, QObject *parent = 0);
	Material(const Vector3f &, QObject *parent = 0);
	Material(const Texture *, const Vector3f &, float, float, QObject *parent = 0);
	~Material();

	Texture *texture() const { return m_texture; }
	Vector3f color() const { return m_color; }
	float specularIntensity() const { return m_specularIntensity; }
	float specularExponent() const { return m_specularExponent; }
	void setTexture(const Texture *);
	void setColor(const Vector3f &);
	void setSpecularIntensity(float specularIntensity) { m_specularIntensity = specularIntensity; }
	void setSpecularExponent(float specularExponent) { m_specularExponent = specularExponent; }

private:
	Texture *m_texture;
	Vector3f m_color;
	float m_specularIntensity;
	float m_specularExponent;
};

#endif // MATERIAL_H
