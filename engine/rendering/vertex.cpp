#include "vertex.h"

Vertex::Vertex(const Vector3f &position, QObject *parent) :
	QObject(parent),
	position(position),
	textureCoordinate(Vector2f(0, 0)),
	normal(Vector3f(0, 0, 0))
{}

Vertex::Vertex(const Vertex &other, QObject *parent) :
	QObject(parent),
	position(other.position),
	textureCoordinate(other.textureCoordinate),
	normal(other.normal)
{}

Vertex::Vertex(const Vector3f &position, const Vector2f &textureCoordinate, QObject *parent) :
	QObject(parent),
	position(position),
	textureCoordinate(textureCoordinate),
	normal(Vector3f(0, 0, 0))
{}

Vertex::Vertex(const Vector3f &position, const Vector2f &textureCoordinate, const Vector3f &normal,
			   QObject *parent) :
	QObject(parent),
	position(position),
	textureCoordinate(textureCoordinate),
	normal(normal)
{}

Vertex &Vertex::operator =(const Vertex &other)
{
	if(&other == this)
		return *this;

	position = other.position;
	textureCoordinate = other.textureCoordinate;
	normal = other.normal;

	return *this;
}
