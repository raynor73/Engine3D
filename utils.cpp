#include <cmath>
#include "utils.h"
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QImage>
#include "geometry/vertex.h"

namespace Utils
{

QString loadShader(const QString &filename)
{
	QFile shaderFile(QString(":/resources/shaders/%1").arg(filename));
	shaderFile.open(QFile::ReadOnly | QFile::Text);

	QTextStream shaderStream(&shaderFile);

	QString shaderText = shaderStream.readAll();

	shaderFile.close();

	return shaderText;
}

float toRadians(float degrees)
{
	return degrees * M_PI / 180;
}

void loadMesh(const QString &filename, Mesh &outMesh, bool shouldCalculateNormals)
{
	QFile meshFile(QString(":/resources/models/%1").arg(filename));
	meshFile.open(QFile::ReadOnly | QFile::Text);
	QList<Vertex> vertices;
	QVector<unsigned int> indices;

	QTextStream meshStream(&meshFile);

	while (!meshStream.atEnd()) {
		auto line = meshStream.readLine();
		auto tokens = line.split(' ');

		if (tokens.size() == 4) {
			if (tokens.at(0) == "v") {
				auto x = tokens.at(1).toFloat();
				auto y = tokens.at(2).toFloat();
				auto z = tokens.at(3).toFloat();
				vertices += Vertex(Vector3f(x, y, z));
			} else if (tokens.at(0) == "f") {
				for (int i = 1; i <= 3; i++)
					indices += tokens.at(i).toInt() - 1;
			}
		}
	}

	meshFile.close();

	outMesh.setVertices(vertices, indices, shouldCalculateNormals);
}

Texture *newTexture(QOPENGLFUNCTIONS_CLASSNAME &f, const QString &filename)
{
	QImage image;
	image.load(QString(":/resources/textures/%1").arg(filename));
	if (image.format() != QImage::Format_RGBA8888)
		image = image.convertToFormat(QImage::Format_RGBA8888);

	GLuint textureID;
	f.glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
				 image.constBits());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return new Texture(f, textureID);
}

}
