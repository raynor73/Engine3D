#ifndef MESH_H
#define MESH_H

#include <QObject>
#include <engine/rendering/qopenglfunctions_selector.h>
#include <QList>
#include <engine/rendering/vertex.h>

class Mesh : public QObject
{
	Q_OBJECT
public:
	Mesh(QOPENGLFUNCTIONS_CLASSNAME &, QObject *parent = 0);
	Mesh(QOPENGLFUNCTIONS_CLASSNAME &, const QString &filename, QObject *parent = 0);
	~Mesh();

	void setVertices(QList<Vertex> &, const QVector<unsigned int> &);
	void setVertices(QList<Vertex> &, const QVector<unsigned int> &, bool);
	void draw();

private:
	QOPENGLFUNCTIONS_CLASSNAME &f;

	GLuint m_vertexBufferObjectName;
	GLuint m_indexBufferObjectName;
	int m_numberOfIndices;
	unsigned char *m_temporaryVertexBuffer;

	void loadMesh(const QString &filename);
	void calculateNormals(QList<Vertex> &, const QVector<unsigned int> &);
};

#endif // MESH_H
