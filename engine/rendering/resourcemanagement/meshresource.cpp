#include "meshresource.h"

MeshResource::MeshResource(QObject *parent) : QObject(parent)
{
	glGenBuffers(1, &m_vertexBufferObjectName);
	glGenBuffers(1, &m_indexBufferObjectName);
}

MeshResource::~MeshResource()
{
	glDeleteBuffers(1, &m_vertexBufferObjectName);
	glDeleteBuffers(1, &m_indexBufferObjectName);
}
