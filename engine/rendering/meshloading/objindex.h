#ifndef OBJINDEX_H
#define OBJINDEX_H

class OBJIndex
{
public:
	int vertexIndex() const { return m_vertexIndex; }
	void setVertexIndex(int vertexIndex) { m_vertexIndex = vertexIndex; }

	int textureCoordinateIndex() const { return m_textureCoordinateIndex; }
	void setTextureCoordinateIndex(int textureCoordinateIndex) { m_textureCoordinateIndex = textureCoordinateIndex; }

	int normalIndex() const { return m_normalIndex; }
	void setNormalIndex(int normalIndex) { m_normalIndex = normalIndex; }

private:
	int m_vertexIndex;
	int m_textureCoordinateIndex;
	int m_normalIndex;
};

#endif // OBJINDEX_H
