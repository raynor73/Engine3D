	#ifndef SHADER_H
#define SHADER_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QList>
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
	Shader(QOPENGLFUNCTIONS_CLASSNAME &, const QString &name, GLuint vertexArrayName, QObject *parent = 0);
	~Shader();

	void setUniformi(const QString &, int);
	void setUniformf(const QString &, float);
	void setUniform(const QString &, const Vector3f &);
	void setUniform(const QString &, const Matrix4f &);
	GLint positionAttributeIndex() { return m_positionAttributeIndex; }
	void linkProgram();
	void bind();
	virtual void updateUniforms(Transform &, Material &, RenderingEngine &) = 0;

protected:
	QOPENGLFUNCTIONS_CLASSNAME &f;
	GLuint m_programReference;

private:
	static QString loadShader(const QString &filename);

	struct StructField {
		StructField(QString type, QString name) :
			type(type),
			name(name)
		{}

		QString type;
		QString name;
	};

	GLint m_positionAttributeIndex;
	QMap<QString, GLint> m_uniformLocations;

	void compileShader(const QString &, GLenum);
	QMap<QString, QList<StructField>> findUniformStructs(const QString &shaderText);
	void addUniformWithStructCheck(QString uniformType, QString uniformName,
								   QMap<QString, QList<StructField>> structsWithFields);
	void addAllUniforms(const QString &shaderText);
	void addUniform(const QString &);
	void setVertexShader(const QString &);
	void setGeometryShader(const QString &);
	void setFragmentShader(const QString &);
};

#endif // SHADER_H
