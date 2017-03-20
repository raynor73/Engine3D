#ifndef MESH_H
#define MESH_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QList>
#include "vertex.h"

class Mesh : public QObject
{
	Q_OBJECT
public:
	explicit Mesh(QOpenGLFunctions &, QObject *parent = 0);
	~Mesh();

	void setVertices(const QList<Vertex> &);
	void draw();

private:
	QOpenGLFunctions &f;

	GLuint m_bufferObjectName;
	int m_numberOfVertices;
	unsigned char *m_buffer;
};

#endif // MESH_H
