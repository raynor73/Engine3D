#include "meshresource.h"

MeshResource::MeshResource(int numberOfIndices) :
	m_numberOfIndices(numberOfIndices)
{
	_glGenBuffers(1, &m_vertexBufferObjectName);
	_glGenBuffers(1, &m_indexBufferObjectName);
}

MeshResource::~MeshResource()
{
	_glDeleteBuffers(1, &m_vertexBufferObjectName);
	_glDeleteBuffers(1, &m_indexBufferObjectName);
}
