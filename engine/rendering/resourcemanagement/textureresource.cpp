#include "textureresource.h"

TextureResource::TextureResource()
{
	glGenTextures(1, &m_id);
}

TextureResource::~TextureResource()
{
	glDeleteTextures(1, &m_id);
}
