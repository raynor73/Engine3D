#include "material.h"

Material::Material(const Texture &texture, const Vector3f &color, QObject *parent) :
	QObject(parent),
	m_texture(new Texture(texture)),
	m_color(color)
{}

Material::Material(const Vector3f &color, QObject *parent) :
	QObject(parent),
	m_texture(NULL),
	m_color(color)
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
