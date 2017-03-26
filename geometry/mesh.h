#ifndef MESH_H
#define MESH_H

#include <QObject>
#include "qopenglfunctions_selector.h"
#include <QList>
#include "vertex.h"

class Mesh : public QObject
{
	Q_OBJECT
public:
	explicit Mesh(QOPENGLFUNCTIONS_CLASSNAME &, QObject *parent = 0);
	~Mesh();

	void setVertices(const QList<Vertex> &, const QVector<unsigned int> &);
	void draw();

private:
	QOPENGLFUNCTIONS_CLASSNAME &f;

	GLuint m_vertexBufferObjectName;
	GLuint m_indexBufferObjectName;
	int m_numberOfIndices;
	unsigned char *m_temporaryVertexBuffer;
};

#endif // MESH_H
