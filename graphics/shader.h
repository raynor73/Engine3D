#ifndef SHADER_H
#define SHADER_H

#include <QObject>
#include <QString>
#include <QMap>
#include <graphics/material.h>
#include "geometry/vector3f.h"
#include "geometry/matrix4f.h"
#include "qopenglfunctions_selector.h"

class Shader : public QObject
{
	Q_OBJECT
public:
	explicit Shader(QOPENGLFUNCTIONS_CLASSNAME &, QObject *parent = 0);
	~Shader();

	void setVertexShader(const QString &);
	void setGeometryShader(const QString &);
	void setFragmentShader(const QString &);
	void addUniform(const QString &);
	void setUniformi(const QString &, int);
	void setUniformf(const QString &, float);
	void setUniform(const QString &, const Vector3f &);
	void setUniform(const QString &, const Matrix4f &);
	GLint positionAttributeIndex() { return m_positionAttributeIndex; }
	void linkProgram();
	void bind();
	virtual void updateUniforms(const Matrix4f &, const Matrix4f &, const Material &) = 0;

protected:
	QOPENGLFUNCTIONS_CLASSNAME &f;
	GLuint m_programReference;
	void setVertexShaderFromFile(const QString &);
	void setGeometryShaderFromFile(const QString &);
	void setFragmentShaderFromFile(const QString &);

private:
	GLint m_positionAttributeIndex;
	QMap<QString, GLint> m_uniformLocations;

	static QString loadShader(const QString &);

	void compileShader(const QString &, GLenum);
};

#endif // SHADER_H
