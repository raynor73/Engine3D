#include <QStringList>
#include <QByteArray>
#include <QDebug>
#include "shader.h"
#include "renderutils.h"

Shader::Shader(QOpenGLFunctions_3_3_Core &f, QObject *parent) :
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

	/*m_positionAttributeIndex = f.glGetAttribLocation(m_programReference, "position");
	Q_ASSERT(m_positionAttributeIndex >= 0 && m_positionAttributeIndex != GL_INVALID_OPERATION);*/
}

void Shader::compileShader(QString &text, GLenum type)
{
	GLuint shaderReference = f.glCreateShader(type);
	Q_ASSERT(shaderReference != 0);

	/*QStringList qtSourceStrings = text.split('\n');
	char **rawSourceStrings = new char*[qtSourceStrings.size()];
	GLint *stringLengths = new GLint[qtSourceStrings.size()];
	for (int i = 0; i < qtSourceStrings.size(); i++) {
		QByteArray stringBytes = qtSourceStrings.at(i).toLocal8Bit();
		rawSourceStrings[i] = new char[stringBytes.size() + 1];

		std::fill(rawSourceStrings[i], rawSourceStrings[i] + stringBytes.size() + 1, 0);

		if (stringBytes.size() > 0)
			std::copy(stringBytes.data(), stringBytes.data() + stringBytes.size(),
					  rawSourceStrings[i]);

		stringLengths[i] = stringBytes.size();

		qDebug() << QString::fromLocal8Bit(rawSourceStrings[i]);
		qDebug() << stringLengths[i];
	}

	f.glShaderSource(shaderReference, qtSourceStrings.size(),
					 const_cast<const char **>(rawSourceStrings), stringLengths);*/
	QByteArray textBytes = text.toLocal8Bit();
	const char *rawText = textBytes.data();
	GLint textLength = textBytes.length();
	f.glShaderSource(shaderReference, 1, &rawText, &textLength);
	f.glCompileShader(shaderReference);

	char tmp[1024];
	GLsizei length;
	f.glGetShaderInfoLog(shaderReference, 1024, &length, tmp);
	qDebug() << QString::fromLocal8Bit(tmp);

	Q_ASSERT(RenderUtils::glGetShader(f, shaderReference, GL_COMPILE_STATUS) == GL_TRUE);

	f.glAttachShader(m_programReference, shaderReference);

	/*for (int i = 0; i < qtSourceStrings.size(); i++)
		delete rawSourceStrings[i];

	delete rawSourceStrings;
	delete stringLengths;*/
}
