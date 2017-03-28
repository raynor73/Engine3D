#include "texture.h"

Texture::Texture(QOPENGLFUNCTIONS_CLASSNAME &f, int id, QObject *parent) :
	QObject(parent),
	f(f),
	m_id(id)
{}

Texture::Texture(const Texture &other) :
	QObject(other.parent()),
	f(other.f),
	m_id(other.m_id)
{}

void Texture::bind()
{
	f.glBindTexture(GL_TEXTURE_2D, m_id);
}
