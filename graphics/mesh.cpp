#include <QVector>
#include "mesh.h"

Mesh::Mesh(QOPENGLFUNCTIONS_CLASSNAME &f, QObject *parent) :
	QObject(parent),
	f(f),
	m_numberOfIndices(0),
	m_temporaryVertexBuffer(NULL)
{
	f.glGenBuffers(1, &m_vertexBufferObjectName);
	f.glGenBuffers(1, &m_indexBufferObjectName);
}

Mesh::~Mesh()
{
	f.glDeleteBuffers(1, &m_vertexBufferObjectName);
	f.glDeleteBuffers(1, &m_indexBufferObjectName);
	if (m_temporaryVertexBuffer != NULL) {
		delete m_temporaryVertexBuffer;
		m_temporaryVertexBuffer = NULL;
	}
}

void Mesh::setVertices(const QList<Vertex> &vertices, const QVector<unsigned int> &indices)
{
	if (m_temporaryVertexBuffer != NULL)
		delete m_temporaryVertexBuffer;

	m_numberOfIndices = indices.size();

	auto numberOfVertices = vertices.size();

	auto sizeOfVertexBuffer = numberOfVertices * Vertex::SIZE * sizeof(float);
	m_temporaryVertexBuffer = new unsigned char[sizeOfVertexBuffer];
	auto m_floatBuffer = reinterpret_cast<float *>(m_temporaryVertexBuffer);
	for (int i = 0; i < numberOfVertices; i++) {
		int base = i * Vertex::SIZE;
		const Vector3f &position = vertices.at(i).position;

		m_floatBuffer[base] = position.x;
		m_floatBuffer[base + 1] = position.y;
		m_floatBuffer[base + 2] = position.z;
	}

	f.glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjectName);
	f.glBufferData(GL_ARRAY_BUFFER, sizeOfVertexBuffer, m_temporaryVertexBuffer, GL_STATIC_DRAW);

	f.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObjectName);
	f.glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numberOfIndices * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void Mesh::draw()
{
	f.glEnableVertexAttribArray(0);

	f.glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjectName);
	f.glVertexAttribPointer(0, Vertex::SIZE, GL_FLOAT, GL_FALSE, 0, 0);

	f.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObjectName);

	f.glDrawElements(GL_TRIANGLES, m_numberOfIndices, GL_UNSIGNED_INT, 0);

	f.glDisableVertexAttribArray(0);
}
