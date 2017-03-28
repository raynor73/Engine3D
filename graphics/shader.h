#ifndef SHADER_H
#define SHADER_H

#include <QObject>
#include <QString>
#include <QMap>
#include "geometry/vector3f.h"
#include "geometry/matrix4f.h"
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
	void addUniform(const QString &);
	void setUniformi(const QString &, int);
	void setUniformf(const QString &, float);
	void setUniform(const QString &, const Vector3f &);
	void setUniform(const QString &, Matrix4f &);
	GLint positionAttributeIndex() { return m_positionAttributeIndex; }
	void linkProgram();
	void bind();

private:
	QOPENGLFUNCTIONS_CLASSNAME &f;
	GLuint m_programReference;
	GLint m_positionAttributeIndex;
	QMap<QString, GLint> m_uniformLocations;

	void compileShader(QString &, GLenum);
};

#endif // SHADER_H
