#include "meshresource.h"

MeshResource::MeshResource()
{
	_glGenBuffers(1, &m_vertexBufferObjectName);
	_glGenBuffers(1, &m_indexBufferObjectName);
}

MeshResource::~MeshResource()
{
	_glDeleteBuffers(1, &m_vertexBufferObjectName);
	_glDeleteBuffers(1, &m_indexBufferObjectName);
}
