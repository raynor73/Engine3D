#include "texture.h"
#include <QImage>

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

Texture &Texture::operator =(const Texture &other)
{
	if (&other == this)
		return *this;

	f = other.f;
	m_id = other.m_id;

	return *this;
}

Texture::Texture(QOPENGLFUNCTIONS_CLASSNAME &f, const QString &filename, QObject *parent) :
	QObject(parent),
	f(f)
{
	QImage image;
	image.load(QString(":/resources/textures/%1").arg(filename));
	if (image.format() != QImage::Format_RGBA8888)
		image = image.convertToFormat(QImage::Format_RGBA8888);

	GLuint textureID;
	f.glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
				 image.constBits());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	m_id = textureID;
}
