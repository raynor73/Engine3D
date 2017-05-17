#ifndef MATERIAL_H
#define MATERIAL_H

#include <QObject>
#include <QMap>
#include <QString>
#include <engine/core/vector3f.h>
#include "texture.h"

class Material : public QObject
{
	Q_OBJECT

public:
	explicit Material(QObject *parent = 0);

	void addTexture(const QString &name, Texture *texture) { m_textures[name] = texture; }
	Texture *findTexture(const QString &name) { return m_textures[name]; }

	void addVector3f(const QString &name, const Vector3f &vector) { m_vectors3f[name] = vector; }
	Vector3f findVector3f(const QString &name) const { return m_vectors3f[name]; }

	void addFloat(const QString &name, float value) { m_floats[name] = value; }
	float findFloat(const QString &name) const { return m_floats[name]; }

private:
	QMap<QString, Texture *> m_textures;
	QMap<QString, Vector3f> m_vectors3f;
	QMap<QString, float> m_floats;
};

#endif // MATERIAL_H
