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

	auto sizeOfBuffer = m_numberOfVertices * Vertex::SIZE * sizeof(float);
	m_buffer = new unsigned char[sizeOfBuffer];
	auto m_floatBuffer = reinterpret_cast<float *>(m_buffer);
	for (int i = 0; i < m_numberOfVertices; i++) {
		int base = i * Vertex::SIZE;
		const Vector3f &position = vertices.at(i).position;

		m_floatBuffer[base] = position.x;
		m_floatBuffer[base + 1] = position.y;
		m_floatBuffer[base + 2] = position.z;
	}

	f.glBindBuffer(GL_ARRAY_BUFFER, m_bufferObjectName);
	f.glBufferData(GL_ARRAY_BUFFER, sizeOfBuffer, m_buffer, GL_STATIC_DRAW);
}

void Mesh::draw()
{
	f.glEnableVertexAttribArray(m_positionAttributeIndex);

	f.glBindBuffer(GL_ARRAY_BUFFER, m_bufferObjectName);
	//f.glVertexAttribPointer(m_positionAttributeIndex, Vertex::SIZE, GL_FLOAT, GL_FALSE, Vertex::SIZE * sizeof(float), 0);
	f.glVertexAttribPointer(m_positionAttributeIndex, Vertex::SIZE, GL_FLOAT, GL_FALSE, 0, 0);

	f.glDrawArrays(GL_TRIANGLES, 0, m_numberOfVertices);

	f.glDisableVertexAttribArray(m_positionAttributeIndex);
}
