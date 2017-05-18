#include "indexedmodel.h"

IndexedModel::IndexedModel(QObject *parent) : QObject(parent) {}

IndexedModel::IndexedModel(const IndexedModel &other) :
	QObject(other.parent()),
	m_positions(other.m_positions),
	m_textureCoordinates(other.m_textureCoordinates),
	m_normals(other.m_normals),
	m_indices(other.m_indices)
{}

IndexedModel &IndexedModel::operator =(const IndexedModel &other)
{
	if (this == &other)
		return *this;

	m_positions = other.m_positions;
	m_textureCoordinates = other.m_textureCoordinates;
	m_normals = other.m_normals;
	m_indices = other.m_indices;

	return *this;
}

void IndexedModel::calculateNormals()
{
	for (int i = 0; i < m_indices.size(); i += 3) {
		int i0 = m_indices[i];
		int i1 = m_indices[i + 1];
		int i2 = m_indices[i + 2];

		Vector3f v1 = m_positions[i1] - m_positions[i0];
		Vector3f v2 = m_positions[i2] - m_positions[i0];

		Vector3f normal = v1.cross(v2).normalized();

		m_normals[i0] += normal;
		m_normals[i1] += normal;
		m_normals[i2] += normal;
	}

	for (int i = 0; i < m_normals.size(); i++)
		m_normals[i] = m_normals[i].normalized();
}
