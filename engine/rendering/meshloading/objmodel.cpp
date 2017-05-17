#include "objmodel.h"
#include <QTextStream>

OBJModel::OBJModel(QObject *parent) :
	QObject(parent)
{
	/*QFile meshFile(QString(":/resources/models/%1").arg(filename));
	meshFile.open(QFile::ReadOnly | QFile::Text);
	QList<Vertex> vertices;
	QVector<unsigned int> indices;*/

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
			}
			/*} else if (tokens.at(0) == "f") {
				for (int i = 1; i <= 3; i++)
					indices += tokens.at(i).toInt() - 1;
			}*/
		}
	}

	meshFile.close();

	setVertices(vertices, indices, shouldCalculateNormals);
}
