#include <QStringList>
#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include "shader.h"
#include <engine/rendering/renderutils.h>
#include <engine/rendering/renderingengine.h>
#include <engine/components/camera.h>
#include <engine/core/transform.h>

Shader::Shader(QOPENGLFUNCTIONS_CLASSNAME &f, GLuint vertexArrayName, QObject *parent) :
	QObject(parent),
	f(f)
{
	f.glBindVertexArray(vertexArrayName);

	m_programReference = f.glCreateProgram();
	Q_ASSERT(m_programReference != 0);
}

Shader::~Shader()
{
	f.glDeleteProgram(m_programReference);
}

void Shader::setVertexShaderFromFile(const QString &filename)
{
	compileShader(loadShader(filename), GL_VERTEX_SHADER);
}

void Shader::setGeometryShaderFromFile(const QString &filename)
{
	compileShader(loadShader(filename), GL_GEOMETRY_SHADER);
}

void Shader::setFragmentShaderFromFile(const QString &filename)
{
	compileShader(loadShader(filename), GL_FRAGMENT_SHADER);
}

void Shader::setVertexShader(const QString &text)
{
	compileShader(text, GL_VERTEX_SHADER);
}

void Shader::setGeometryShader(const QString &text)
{
	compileShader(text, GL_GEOMETRY_SHADER);
}

void Shader::setFragmentShader(const QString &text)
{
	compileShader(text, GL_FRAGMENT_SHADER);
}

void Shader::linkProgram()
{
	f.glLinkProgram(m_programReference);
	Q_ASSERT(RenderUtils::glGetProgram(f, m_programReference, GL_LINK_STATUS) == GL_TRUE);

	f.glValidateProgram(m_programReference);
	Q_ASSERT(RenderUtils::glGetProgram(f, m_programReference, GL_VALIDATE_STATUS) == GL_TRUE);
}

void Shader::bind()
{
	f.glUseProgram(m_programReference);
}

void Shader::compileShader(const QString &text, GLenum type)
{
	GLuint shaderReference = f.glCreateShader(type);
	Q_ASSERT(shaderReference != 0);

	QByteArray textBytes = text.toLocal8Bit();
	const char *rawText = textBytes.data();
	GLint textLength = textBytes.length();
	f.glShaderSource(shaderReference, 1, &rawText, &textLength);
	f.glCompileShader(shaderReference);

	Q_ASSERT(RenderUtils::glGetShader(f, shaderReference, GL_COMPILE_STATUS) == GL_TRUE);

	f.glAttachShader(m_programReference, shaderReference);
}

QMap<QString, QList<QString>> Shader::findUniformStructs(const QString &shaderText)
{
	QMap<QString, QList<QString>> structsWithFields;

	QRegularExpression structRe("^struct (\\w+)\\n\\{((.|\\n)*?)\\};", QRegularExpression::MultilineOption);
	QRegularExpression fieldRe("(\\w+) (\\w+);");

	QRegularExpressionMatchIterator structMatchIterator = structRe.globalMatch(shaderText);
	while (structMatchIterator.hasNext()) {
		QRegularExpressionMatch structMatch = structMatchIterator.next();
		QRegularExpressionMatchIterator fieldMatchIterator = fieldRe.globalMatch(structMatch.captured(2));
		QList<QString> fields;
		while (fieldMatchIterator.hasNext()) {
			QRegularExpressionMatch fieldMatch = fieldMatchIterator.next();
			//qDebug() << fieldMatch.captured(1) << fieldMatch.captured(2);
			fields += fieldMatch.captured(2);
		}
		structsWithFields[structMatch.captured(1)] = fields;
	}

	return structsWithFields;
}

void Shader::addAllUniforms(const QString &shaderText)
{
	QMap<QString, QList<QString>> structsWithFields = findUniformStructs(shaderText);

	QRegularExpression re("uniform (\\w*?) ([\\w]+)");
	QRegularExpressionMatchIterator i = re.globalMatch(shaderText);
	while (i.hasNext()) {
		QRegularExpressionMatch match= i.next();
		addUniform(match.captured(2));
	}
}

void Shader::addUniform(const QString &uniformName)
{
	GLint uniformLocation = f.glGetUniformLocation(m_programReference, uniformName.toLocal8Bit());
	Q_ASSERT(uniformLocation >= 0);

	m_uniformLocations[uniformName] = uniformLocation;
}

void Shader::setUniformi(const QString &uniformName, int value)
{
	f.glUniform1i(m_uniformLocations[uniformName], value);
}

void Shader::setUniformf(const QString &uniformName, float value)
{
	f.glUniform1f(m_uniformLocations[uniformName], value);
}

void Shader::setUniform(const QString &uniformName, const Vector3f &value)
{
	f.glUniform3f(m_uniformLocations[uniformName], value.x, value.y, value.z);
}

void Shader::setUniform(const QString &uniformName, const Matrix4f &value)
{
	f.glUniformMatrix4fv(m_uniformLocations[uniformName], 1, GL_TRUE, value.getM().data());
}

QString Shader::loadShader(const QString &filename)
{
	QFile shaderFile(QString(":/resources/shaders/%1").arg(filename));
	shaderFile.open(QFile::ReadOnly | QFile::Text);

	QTextStream shaderStream(&shaderFile);

	QString shaderText;
	while (!shaderStream.atEnd()) {
		QString line = shaderStream.readLine();

		QRegularExpression re("#include \"([a-z\\.]+)\"");
		QRegularExpressionMatch match = re.match(line);
		if (match.hasMatch()) {
			shaderText.append(loadShader(match.captured(1)));
		} else {
			shaderText.append(line).append("\n");
		}
	}

	shaderFile.close();

	return shaderText;
}
