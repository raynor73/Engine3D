#ifndef VERTEX_H
#define VERTEX_H

#include <QObject>
#include "vector3f.h"

class Vertex : public QObject
{
	Q_OBJECT
public:
	static const int SIZE = 3;

	Vector3f position;

	explicit Vertex(const Vector3f &, QObject *parent = 0);
	Vertex(const Vertex &, QObject *parent = 0);

	Vertex &operator =(const Vertex &);
};

#endif // VERTEX_H
