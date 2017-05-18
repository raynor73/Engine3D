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

		if (tokens.size() == 4) {
			if (tokens.at(0) == "v") {
				auto x = tokens.at(1).toFloat();
				auto y = tokens.at(2).toFloat();
				auto z = tokens.at(3).toFloat();
				m_vertices += Vector3f(x, y, z);
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
	}

	meshFile.close();
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
