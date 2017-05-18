#ifndef VERTEX_H
#define VERTEX_H

#include <QObject>
#include <engine/core/vector3f.h>
#include <engine/core/vector2f.h>

class Vertex : public QObject
{
	Q_OBJECT
public:
	static const int SIZE = 8;

	Vector3f position;
	Vector2f textureCoordinate;
	Vector3f normal;

	Vertex(const Vector3f &position, QObject *parent = 0);
	Vertex(const Vector3f &position, const Vector2f &textureCoordinate, QObject *parent = 0);
	Vertex(const Vector3f &position, const Vector2f &textureCoordinate, const Vector3f &normal, QObject *parent = 0);
	Vertex(const Vertex &, QObject *parent = 0);

	Vertex &operator =(const Vertex &);
};

#endif // VERTEX_H
