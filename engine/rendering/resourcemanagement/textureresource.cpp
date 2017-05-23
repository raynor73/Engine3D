#include "textureresource.h"

TextureResource::TextureResource(GLuint id) :
	m_id(id)
{}

TextureResource::~TextureResource()
{
	glDeleteTextures(1, &m_id);
}
