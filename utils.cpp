#include <cmath>
#include "utils.h"
#include <QFile>
#include <QTextStream>

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

inline float toRadians(float degrees)
{
	return degrees * M_PI / 180;
}

}
