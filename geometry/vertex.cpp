#include "vertex.h"

Vertex::Vertex(const Vector3f &position, QObject *parent) :
	QObject(parent),
	position(position),
	textureCoordinate(Vector2f(0, 0))
{}

Vertex::Vertex(const Vertex &other, QObject *parent) :
	QObject(parent),
	position(other.position),
	textureCoordinate(other.textureCoordinate)
{}

Vertex::Vertex(const Vector3f &position, const Vector2f &textureCoordinate, QObject *parent) :
	QObject(parent),
	position(position),
	textureCoordinate(textureCoordinate)
{}

Vertex &Vertex::operator =(const Vertex &other)
{
	if(&other == this)
		return *this;

	position = other.position;
	textureCoordinate = other.textureCoordinate;

	return *this;
}
