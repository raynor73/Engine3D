#ifndef SHADER_H
#define SHADER_H

#include <QObject>
#include <QString>
#include <QOpenGLFunctions_3_3_Core>

class Shader : public QObject
{
	Q_OBJECT
public:
	explicit Shader(QOpenGLFunctions_3_3_Core &, QObject *parent = 0);
	~Shader();

	void setVertexShader(QString &);
	void setGeometryShader(QString &);
	void setFragmentShader(QString &);
	GLint positionAttributeIndex() { return m_positionAttributeIndex; }
	void linkProgram();
	void bind();

private:
	QOpenGLFunctions_3_3_Core &f;
	GLuint m_programReference;
	GLint m_positionAttributeIndex;

	void compileShader(QString &, GLenum);
};

#endif // SHADER_H
