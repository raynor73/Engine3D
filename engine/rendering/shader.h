	#ifndef SHADER_H
#define SHADER_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QList>
#include <QWeakPointer>
#include <QSharedPointer>
#include <engine/rendering/material.h>
#include <engine/core/vector3f.h>
#include <engine/core/matrix4f.h>
#include <engine/rendering/qopenglfunctions_selector.h>
#include <engine/rendering/resourcemanagement/shaderresource.h>

class RenderingEngine;
class Camera;
class Transform;
class BaseLight;
class DirectionalLight;
class PointLight;
class SpotLight;
class Shader : public QObject
{
	Q_OBJECT
public:
	Shader(QOPENGLFUNCTIONS_CLASSNAME &, const QString &name, GLuint vertexArrayName, QObject *parent = 0);

	void setUniformi(const QString &, int);
	void setUniformf(const QString &, float);
	void setUniform(const QString &, const Vector3f &);
	void setUniform(const QString &, const Matrix4f &);
	GLint positionAttributeIndex() { return m_positionAttributeIndex; }
	void linkProgram();
	void bind();
	virtual void updateUniforms(Transform &, Material &, RenderingEngine &);

protected:
	QOPENGLFUNCTIONS_CLASSNAME &f;

private:
	static QMap<QString, QWeakPointer<ShaderResource>> s_loadedShaders;

	static QString loadShader(const QString &filename);

	struct StructField {
		StructField(QString type, QString name) :
			type(type),
			name(name)
		{}

		QString type;
		QString name;
	};

	struct Uniform : StructField {
		Uniform(QString type, QString name) : StructField(type, name) {}
	};

	QSharedPointer<ShaderResource> m_shaderResource;

	GLint m_positionAttributeIndex;
	QMap<QString, GLint> m_uniformLocations;
	QList<Uniform> m_uniforms;

	void compileShader(const QString &, GLenum);
	QMap<QString, QList<StructField>> findUniformStructs(const QString &shaderText);
	void addUniform(QString uniformType, QString uniformName,
								   QMap<QString, QList<StructField>> structsWithFields);
	void addAllUniforms(const QString &shaderText);
	void setVertexShader(const QString &);
	void setGeometryShader(const QString &);
	void setFragmentShader(const QString &);
	void setUniform(const QString &, const BaseLight &);
	void setUniform(const QString &, DirectionalLight &);
	void setUniform(const QString &, PointLight &);
	void setUniform(const QString &, SpotLight &);
	void loadShaderAndPutToCache(const QString &name);
};

#endif // SHADER_H
