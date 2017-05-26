#ifndef MATERIAL_H
#define MATERIAL_H

#include <QMap>
#include <QString>
#include <engine/core/vector3f.h>
#include <engine/rendering/resourcemanagement/mappedvalues.h>
#include "texture.h"

class Material : public MappedValues
{
public:
	Material() {}

	void addTexture(const QString &name, Texture *texture) { m_textures[name] = texture; }
	Texture *findTexture(const QString &name) { return m_textures[name]; }

	Material(const Material &) = delete;
	Material &operator =(const Material &) = delete;

private:
	QMap<QString, Texture *> m_textures;
};

#endif // MATERIAL_H
