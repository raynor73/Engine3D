#include "mesh.h"

Mesh::Mesh(QOpenGLFunctions &f, QObject *parent) :
	QObject(parent),
	f(f),
	m_numberOfVertices(0),
	m_buffer(NULL)
{
	f.glGenBuffers(1, &m_bufferObjectName);
}

Mesh::~Mesh()
{
	f.glDeleteBuffers(1, &m_bufferObjectName);
	if (m_buffer != NULL) {
		delete m_buffer;
		m_buffer = NULL;
	}
}

void Mesh::setVertices(const QList<Vertex> &vertices)
{
	if (m_buffer != NULL)
		delete m_buffer;

	m_numberOfVertices = vertices.size();

	size_t sizeOfBuffer = m_numberOfVertices * Vertex::SIZE * sizeof(float);
	m_buffer = new unsigned char[sizeOfBuffer];
	for (int i = 0; i < m_numberOfVertices; i++) {
		int base = i * Vertex::SIZE;
		const Vector3f &position = vertices.at(i).position;

		m_buffer[base] = position.x;
		m_buffer[base + 1] = position.y;
		m_buffer[base + 2] = position.z;
	}

	f.glBindBuffer(GL_ARRAY_BUFFER, m_bufferObjectName);
	f.glBufferData(GL_ARRAY_BUFFER, sizeOfBuffer, m_buffer, GL_STATIC_DRAW);
}

void Mesh::draw()
{
	f.glEnableVertexAttribArray(0);

	f.glBindBuffer(GL_ARRAY_BUFFER, m_bufferObjectName);
	f.glVertexAttribPointer(0, Vertex::SIZE, GL_FLOAT, false, 0, 0);

	f.glDrawArrays(GL_TRIANGLES, 0, m_numberOfVertices);

	f.glDisableVertexAttribArray(0);
}
