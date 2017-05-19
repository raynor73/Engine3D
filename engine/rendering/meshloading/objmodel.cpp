#include "objmodel.h"
#include <QTextStream>
#include <QString>
#include <QFile>
#include <unordered_map>

OBJModel::OBJModel(const QString &filename, QObject *parent) :
	QObject(parent),
	m_hasTextureCoordinates(false),
	m_hasNormals(false)
{
	QFile meshFile(QString(":/resources/models/%1").arg(filename));
	meshFile.open(QFile::ReadOnly | QFile::Text);

	QTextStream meshStream(&meshFile);

	while (!meshStream.atEnd()) {
		auto line = meshStream.readLine();
		auto tokens = line.split(' ');

		if (tokens.at(0) == "v") {
			auto x = tokens.at(1).toFloat();
			auto y = tokens.at(2).toFloat();
			auto z = tokens.at(3).toFloat();
			m_positions += Vector3f(x, y, z);
		} else if (tokens.at(0) == "vt") {
			auto x = tokens.at(1).toFloat();
			auto y = tokens.at(2).toFloat();
			m_textureCoordinates += Vector2f(x, y);
		} else if (tokens.at(0) == "vn") {
			auto x = tokens.at(1).toFloat();
			auto y = tokens.at(2).toFloat();
			auto z = tokens.at(3).toFloat();
			m_normals += Vector3f(x, y, z);
		} else if (tokens.at(0) == "f") {
			for (int i = 0; i < tokens.size() - 3; i++) {
				m_indices += parseOBJIndex(tokens.at(1));
				m_indices += parseOBJIndex(tokens.at(2 + i));
				m_indices += parseOBJIndex(tokens.at(3 + i));
			}
		}
	}

	meshFile.close();
}

IndexedModel OBJModel::toIndexedModel() const
{
	IndexedModel indexedModel;
	IndexedModel normalModel;
	std::unordered_map<OBJIndex, int> resultIndexMap;
	std::unordered_map<int, int> normalIndexMap;
	std::unordered_map<int, int> indexMap;

	for (int i = 0; i < m_indices.size(); i++)
	{
		OBJIndex currentIndex = m_indices[i];

		Vector3f currentPosition = m_positions[currentIndex.vertexIndex()];
		Vector2f currentTextureCoordinate;
		Vector3f currentNormal;

		if (m_hasTextureCoordinates)
			currentTextureCoordinate = m_textureCoordinates[currentIndex.textureCoordinateIndex()];

		if (m_hasNormals)
			currentNormal = m_normals[currentIndex.normalIndex()];

		int modelVertexIndex = -1;
		if (resultIndexMap.count(currentIndex) != 0)
			modelVertexIndex = resultIndexMap[currentIndex];

		if (modelVertexIndex == -1) {
			modelVertexIndex = indexedModel.positions().size();
			resultIndexMap[currentIndex] = modelVertexIndex;

			indexedModel.positions() += currentPosition;
			indexedModel.textureCoordinates() += currentTextureCoordinate;
			indexedModel.normals() += currentNormal;
		}

		int normalModelIndex = -1;
		if (normalIndexMap.count(currentIndex.vertexIndex()) != 0)
			normalModelIndex = normalIndexMap[currentIndex.vertexIndex()];

		if (normalModelIndex == -1) {
			normalModelIndex = normalModel.positions().size();
			normalIndexMap[currentIndex.vertexIndex()] = normalModelIndex;

			normalModel.positions() += currentPosition;
			normalModel.textureCoordinates() += currentTextureCoordinate;
			normalModel.normals() += currentNormal;
		}

		indexedModel.indices() += modelVertexIndex;
		normalModel.indices() += normalModelIndex;
		indexMap[modelVertexIndex] = normalModelIndex;
	}

	if (!m_hasNormals) {
		normalModel.calculateNormals();

		for (int i = 0; i < indexedModel.normals().size(); i++)
			indexedModel.normals()[i] = normalModel.normals()[indexMap[i]];
	}

	return indexedModel;
}

OBJIndex OBJModel::parseOBJIndex(const QString &token)
{
	OBJIndex objIndex;

	auto values = token.split('/');

	objIndex.setVertexIndex(values.at(0).toInt() - 1);

	if (values.size() > 1) {
		m_hasTextureCoordinates = true;
		objIndex.setTextureCoordinateIndex(values.at(1).toInt() - 1);

		if (values.size() > 2) {
			m_hasNormals = true;
			objIndex.setNormalIndex(values.at(2).toInt() - 1);
		}
	}

	return objIndex;
}
