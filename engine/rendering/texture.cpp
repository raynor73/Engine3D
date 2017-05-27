#include "texture.h"
#include <QImage>
#include <QDebug>

QMap<QString, QWeakPointer<TextureResource>> Texture::s_loadedTextures;

Texture::Texture(const QString &filename)
{
	if (s_loadedTextures.count(filename) > 0) {
		QWeakPointer<TextureResource> textureResource = s_loadedTextures[filename];
		if (textureResource.isNull()) {
			s_loadedTextures.remove(filename);
			loadTextureAndPutToCache(filename);
		} else {
			qDebug() << "Texture with filename:" << filename << "already loaded, reusing texture";
			m_textureResource = textureResource.toStrongRef();
		}
	} else {
		loadTextureAndPutToCache(filename);
	}
}

void Texture::bind()
{
	bind(0);
}

void Texture::bind(int samplerSlot)
{
	_glActiveTexture(GL_TEXTURE0 + samplerSlot);
	glBindTexture(GL_TEXTURE_2D, m_textureResource->id());
}

void Texture::loadTextureAndPutToCache(const QString &filename)
{
	QImage image;
	image.load(QString(":/resources/textures/%1").arg(filename));
	if (image.format() != QImage::Format_RGBA8888)
		image = image.convertToFormat(QImage::Format_RGBA8888);

	m_textureResource = QSharedPointer<TextureResource>::create();
	glBindTexture(GL_TEXTURE_2D, m_textureResource->id());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
				 image.constBits());

	s_loadedTextures[filename] = m_textureResource.toWeakRef();
}
