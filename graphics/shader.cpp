#include <QStringList>
#include <QByteArray>
#include "shader.h"
#include "renderutils.h"

Shader::Shader(QOpenGLFunctions &f, QObject *parent) :
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
	compileShader(text, GL_FRAGMENT_SHADER_ARB);
}

void Shader::linkProgram()
{
	f.glLinkProgram(m_programReference);
	Q_ASSERT(RenderUtils::glGetShader(f, m_programReference, GL_LINK_STATUS) == GL_TRUE);

	f.glValidateProgram(m_programReference);
	Q_ASSERT(RenderUtils::glGetShader(f, m_programReference, GL_VALIDATE_STATUS) == GL_TRUE);
}

void Shader::bind()
{
	f.glUseProgram(m_programReference);
}

void Shader::compileShader(QString &text, GLenum type)
{
	GLuint shaderReference = f.glCreateShader(type);
	Q_ASSERT(shaderReference != 0);

	QStringList qtSourceStrings = text.split('\n');
	char **rawSourceStrings = new char*[qtSourceStrings.size()];
	GLint *stringLengths = new GLint[qtSourceStrings.size()];
	for (int i = 0; i < qtSourceStrings.size(); i++) {
		QByteArray stringBytes = qtSourceStrings.at(i).toLocal8Bit();
		rawSourceStrings[i] = new char[stringBytes.size()];
		std::copy(&rawSourceStrings[i][0], &rawSourceStrings[i][stringBytes.size() - 1], &stringBytes.data()[0]);
		stringLengths[i] = stringBytes.size();
	}

	f.glShaderSource(shaderReference, qtSourceStrings.size(), const_cast<const char **>(rawSourceStrings),
					 stringLengths);
	f.glCompileShader(shaderReference);

	Q_ASSERT(RenderUtils::glGetShader(f, shaderReference, GL_COMPILE_STATUS) == GL_TRUE);

	f.glAttachShader(m_programReference, shaderReference);

	for (int i = 0; i < qtSourceStrings.size(); i++)
		delete rawSourceStrings[i];

	delete rawSourceStrings;
	delete stringLengths;
}

