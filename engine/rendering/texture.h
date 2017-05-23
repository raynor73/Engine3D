#ifndef TEXTURE_H
#define TEXTURE_H

#include <glwrapper.h>
#include <engine/rendering/resourcemanagement/textureresource.h>
#include <QSharedPointer>

class Texture
{
public:
	Texture(const QString &filename);

	GLuint id() const { return m_textureResource->id(); }
	void bind();

private:
	static QMap<QString, QWeakPointer<TextureResource>> s_loadedTextures;

	QSharedPointer<TextureResource> m_textureResource;

	void loadTextureAndPutToCache(const QString &filename);
};

#endif // TEXTURE_H
