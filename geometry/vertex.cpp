#include "vertex.h"

Vertex::Vertex(const Vector3f &position, QObject *parent) :
	QObject(parent),
	position(position)
{}

Vertex::Vertex(const Vertex &other, QObject *parent) :
	QObject(parent),
	position(other.position)
{}

Vertex &Vertex::operator =(const Vertex &other)
{
	if(&other == this)
		return *this;

	position = other.position;

	return *this;
}
