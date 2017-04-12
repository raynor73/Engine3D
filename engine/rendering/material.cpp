#include "material.h"

Material::Material(Texture *texture, const Vector3f &color, QObject *parent) :
	Material(texture, color, 2, 32, parent)
{}

Material::Material(const Vector3f &color, float specularIntensity, float specularPower,
				   QObject *parent) :
	QObject(parent),
	m_texture(NULL),
	m_color(color),
	m_specularIntensity(specularIntensity),
	m_specularPower(specularPower)
{}

Material::Material(const Vector3f &color, QObject *parent) :
	QObject(parent),
	m_texture(NULL),
	m_color(color),
	m_specularIntensity(2),
	m_specularPower(32)
{}

Material::Material(Texture *texture, const Vector3f &color, float specularIntensity,
				   float specularPower, QObject *parent) :
	QObject(parent),
	m_texture(texture),
	m_color(color),
	m_specularIntensity(specularIntensity),
	m_specularPower(specularPower)
{}

Material::~Material()
{}

void Material::setTexture(Texture *texture)
{
	m_texture = texture;
}

void Material::setColor(const Vector3f &color)
{
	m_color = color;
}
