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

	bool operator== (const OBJIndex &other) const
	{
		return m_vertexIndex == other.m_vertexIndex &&
				m_textureCoordinateIndex == other.m_textureCoordinateIndex &&
				m_normalIndex == other.m_normalIndex;
	}

private:
	int m_vertexIndex;
	int m_textureCoordinateIndex;
	int m_normalIndex;
};

namespace std
{

template <>
struct hash<OBJIndex>
{
	std::size_t operator()(const OBJIndex& k) const
	{
		std::size_t hash = HASH_BASE;

		hash = HASH_MULTIPLIER * hash + k.vertexIndex();
		hash = HASH_MULTIPLIER * hash + k.textureCoordinateIndex();
		hash = HASH_MULTIPLIER * hash + k.normalIndex();

		return hash;
	}

private:
	static const std::size_t HASH_BASE = 17;
	static const std::size_t HASH_MULTIPLIER = 31;
};

}

#endif // OBJINDEX_H
