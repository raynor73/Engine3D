#ifndef MATERIAL_H
#define MATERIAL_H

#include <QObject>
#include <geometry/vector3f.h>
#include "texture.h"

class Material : public QObject
{
	Q_OBJECT

public:
	explicit Material(const Texture &, const Vector3f &, QObject *parent = 0);
	Material (const Vector3f &, QObject *parent = 0);
	~Material();

	Texture *texture() const { return m_texture; }
	Vector3f color() const { return m_color; }
	void setTexture(const Texture *);
	void setColor(const Vector3f &);

private:
	Texture *m_texture;
	Vector3f m_color;
};

#endif // MATERIAL_H
