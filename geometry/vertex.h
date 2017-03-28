#ifndef VERTEX_H
#define VERTEX_H

#include <QObject>
#include "vector3f.h"
#include "vector2f.h"

class Vertex : public QObject
{
	Q_OBJECT
public:
	static const int SIZE = 5;

	Vector3f position;
	Vector2f textureCoordinate;

	explicit Vertex(const Vector3f &, QObject *parent = 0);
	Vertex(const Vector3f &, const Vector2f &, QObject *parent = 0);
	Vertex(const Vertex &, QObject *parent = 0);

	Vertex &operator =(const Vertex &);
};

#endif // VERTEX_H
