#include <QStringList>
#include <QByteArray>
#include <QDebug>
#include <QFile>
#include "shader.h"
#include <engine/rendering/renderutils.h>
#include <engine/rendering/renderingengine.h>

Shader::Shader(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine, QObject *parent) :
	QObject(parent),
	f(f),
	m_renderingEngine(renderingEngine)
{
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
	qDebug() << metaObject()->className() << RenderUtils::glGetProgramInfoLog(f, m_programReference);
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

	QString shaderText = shaderStream.readAll();

	shaderFile.close();

	return shaderText;
}
