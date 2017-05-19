#include "objmodel.h"
#include <QTextStream>
#include <QString>
#include <QFile>

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
	QMap<OBJIndex, int> indexMap;

	int currentVertexIndex = 0;
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

		int prevVertexIndex = -1;

		if (indexMap.contains(currentIndex))
			prevVertexIndex = indexMap[currentIndex];

		if (prevVertexIndex == -1) {
			indexMap[currentIndex] = currentVertexIndex;

			indexedModel.positions() += currentPosition;
			indexedModel.textureCoordinates() += currentTextureCoordinate;
			indexedModel.normals() += currentNormal;
			indexedModel.indices() += currentVertexIndex;
			currentVertexIndex++;
		} else {
			indexedModel.indices() += prevVertexIndex;
		}
		/*for (int j = 0; j < i; j++) {
			OBJIndex oldIndex = m_indices[j];

			if (currentIndex.vertexIndex() == oldIndex.vertexIndex() &&
					currentIndex.textureCoordinateIndex() == oldIndex.textureCoordinateIndex() &&
					currentIndex.normalIndex() == oldIndex.normalIndex()) {
				prevVertexIndex = j;
				break;
			}
		}

		if (prevVertexIndex == -1) {
			indexMap[i] = currentVertexIndex;

			indexedModel.positions() += currentPosition;
			indexedModel.textureCoordinates() += currentTextureCoordinate;
			indexedModel.normals() += currentNormal;
			indexedModel.indices() += currentVertexIndex;
			currentVertexIndex++;
		} else {
			indexedModel.indices() += indexMap[prevVertexIndex];
		}*/
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
