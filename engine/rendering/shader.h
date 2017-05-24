#ifndef SHADER_H
#define SHADER_H

#include <QObject>
#include <QString>
#include <QMap>
#include <engine/rendering/material.h>
#include <engine/core/vector3f.h>
#include <engine/core/matrix4f.h>
#include <engine/rendering/qopenglfunctions_selector.h>
#include <QPointer>

class RenderingEngine;
class Camera;
class Transform;
class Shader : public QObject
{
	Q_OBJECT
public:
	Shader(QOPENGLFUNCTIONS_CLASSNAME &, GLuint vertexArrayName, QObject *parent = 0);
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
	virtual void updateUniforms(Transform &, Material &, RenderingEngine &) = 0;
	void addAllUniforms(const QString &shaderText);
	static QString loadShader(const QString &);

protected:
	QOPENGLFUNCTIONS_CLASSNAME &f;
	GLuint m_programReference;
	void setVertexShaderFromFile(const QString &);
	void setGeometryShaderFromFile(const QString &);
	void setFragmentShaderFromFile(const QString &);

private:
	GLint m_positionAttributeIndex;
	QMap<QString, GLint> m_uniformLocations;

	void compileShader(const QString &, GLenum);
};

#endif // SHADER_H
