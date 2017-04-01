#include <QStringList>
#include <QByteArray>
#include <QDebug>
#include "shader.h"
#include "renderutils.h"

Shader::Shader(QOPENGLFUNCTIONS_CLASSNAME &f, QObject *parent) :
	QObject(parent),
	f(f)
{
	m_programReference = f.glCreateProgram();
	Q_ASSERT(m_programReference != 0);
}

Shader::~Shader()
{
	f.glDeleteProgram(m_programReference);
}

void Shader::setVertexShader(QString &text)
{
	compileShader(text, GL_VERTEX_SHADER);
}

void Shader::setGeometryShader(QString &text)
{
	compileShader(text, GL_GEOMETRY_SHADER);
}

void Shader::setFragmentShader(QString &text)
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

void Shader::compileShader(QString &text, GLenum type)
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

void Shader::setUniform(const QString &uniformName, Matrix4f &value)
{
	f.glUniformMatrix4fv(m_uniformLocations[uniformName], 1, GL_TRUE, value.getM().data());
}
