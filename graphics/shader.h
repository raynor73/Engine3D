#ifndef SHADER_H
#define SHADER_H

#include <QObject>
#include <QString>
#include <QOpenGLFunctions>

class Shader : public QObject
{
	Q_OBJECT
public:
	explicit Shader(QOpenGLFunctions &, QObject *parent = 0);
	~Shader();

	void setVertexShader(QString &);
	void setGeometryShader(QString &);
	void setFragmentShader(QString &);
	void linkProgram();
	void bind();

private:
	QOpenGLFunctions &f;
	GLuint m_programReference;

	void compileShader(QString &, GLenum);
};

#endif // SHADER_H
