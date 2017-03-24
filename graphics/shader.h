#ifndef SHADER_H
#define SHADER_H

#include <QObject>
#include <QString>
#include "qopenglfunctions_selector.h"

class Shader : public QObject
{
	Q_OBJECT
public:
	explicit Shader(QOPENGLFUNCTIONS_CLASSNAME &, QObject *parent = 0);
	~Shader();

	void setVertexShader(QString &);
	void setGeometryShader(QString &);
	void setFragmentShader(QString &);
	GLint positionAttributeIndex() { return m_positionAttributeIndex; }
	void linkProgram();
	void bind();

private:
	QOPENGLFUNCTIONS_CLASSNAME &f;
	GLuint m_programReference;
	GLint m_positionAttributeIndex;

	void compileShader(QString &, GLenum);
};

#endif // SHADER_H
