#include "material.h"

Material::Material(const Texture *texture, const Vector3f &color, QObject *parent) :
	Material(texture, color, 2, 32, parent)
{}

Material::Material(const Vector3f &color, QObject *parent) :
	Material(NULL, color, parent)
{}

Material::Material(const Texture *texture, const Vector3f &color, float specularIntensity, float specularExponent,
				   QObject *parent) :
	QObject(parent),
	m_texture(new Texture(*texture)),
	m_color(color),
	m_specularIntensity(specularIntensity),
	m_specularExponent(specularExponent)
{}

Material::~Material()
{
	if (m_texture != NULL) {
		delete m_texture;
		m_texture = NULL;
	}
}

void Material::setTexture(const Texture *texture)
{
	if (m_texture != NULL) {
		delete m_texture;
		m_texture = NULL;
	}

	if (texture != NULL)
		*m_texture = *texture;
}

void Material::setColor(const Vector3f &color)
{
	m_color = color;
}
