#include <QStringList>
#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include "shader.h"
#include <engine/rendering/renderutils.h>
#include <engine/rendering/renderingengine.h>
#include <engine/components/camera.h>
#include <engine/core/transform.h>
#include <engine/components/baselight.h>
#include <engine/components/directionallight.h>
#include <engine/components/pointlight.h>
#include <engine/components/spotlight.h>

QMap<QString, QWeakPointer<ShaderResource>> Shader::s_loadedShaders;

Shader::Shader(QOPENGLFUNCTIONS_CLASSNAME &f, const QString &name, GLuint vertexArrayName, QObject *parent) :
	QObject(parent),
	f(f)
{
	f.glBindVertexArray(vertexArrayName);

	if (s_loadedShaders.count(name) > 0) {
		QWeakPointer<ShaderResource> shaderResource = s_loadedShaders[name];
		if (shaderResource.isNull()) {
			s_loadedShaders.remove(name);
			loadShaderAndPutToCache(name);
		} else {
			qDebug() << "Shader with name:" << name << "already loaded, reusing program";
			m_shaderResource = shaderResource.toStrongRef();
		}
	} else {
		loadShaderAndPutToCache(name);
	}
}

void Shader::loadShaderAndPutToCache(const QString &name)
{
	m_shaderResource = QSharedPointer<ShaderResource>::create();

	QString vertexShaderText = loadShader(name + ".vsh");
	QString fragmentShaderText = loadShader(name + ".fsh");

	setVertexShader(vertexShaderText);
	setFragmentShader(fragmentShaderText);
	linkProgram();

	addAllUniforms(vertexShaderText);
	addAllUniforms(fragmentShaderText);

	s_loadedShaders[name] = m_shaderResource.toWeakRef();
}

void Shader::setVertexShader(const QString &text)
{
	compileShader(text, GL_VERTEX_SHADER);
}

void Shader::setGeometryShader(const QString &text)
{
	compileShader(text, GL_GEOMETRY_SHADER);
}

void Shader::setFragmentShader(const QString &text)
{
	compileShader(text, GL_FRAGMENT_SHADER);
}

void Shader::linkProgram()
{
	f.glLinkProgram(m_shaderResource->programReference());
	Q_ASSERT(RenderUtils::glGetProgram(f, m_shaderResource->programReference(), GL_LINK_STATUS) == GL_TRUE);

	f.glValidateProgram(m_shaderResource->programReference());
	Q_ASSERT(RenderUtils::glGetProgram(f, m_shaderResource->programReference(), GL_VALIDATE_STATUS) == GL_TRUE);
}

void Shader::bind()
{
	f.glUseProgram(m_shaderResource->programReference());
}

void Shader::compileShader(const QString &text, GLenum type)
{
	GLuint shaderReference = f.glCreateShader(type);
	Q_ASSERT(shaderReference != 0);

	QByteArray textBytes = text.toLocal8Bit();
	const char *rawText = textBytes.data();
	GLint textLength = textBytes.length();
	f.glShaderSource(shaderReference, 1, &rawText, &textLength);
	f.glCompileShader(shaderReference);

	Q_ASSERT(RenderUtils::glGetShader(f, shaderReference, GL_COMPILE_STATUS) == GL_TRUE);

	f.glAttachShader(m_shaderResource->programReference(), shaderReference);
}

QMap<QString, QList<Shader::StructField>> Shader::findUniformStructs(const QString &shaderText)
{
	QMap<QString, QList<StructField>> structsWithFields;

	QRegularExpression structRe("^struct (\\w+)\\n\\{((.|\\n)*?)\\};", QRegularExpression::MultilineOption);
	QRegularExpression fieldRe("(\\w+) (\\w+);");

	QRegularExpressionMatchIterator structMatchIterator = structRe.globalMatch(shaderText);
	while (structMatchIterator.hasNext()) {
		QRegularExpressionMatch structMatch = structMatchIterator.next();
		QRegularExpressionMatchIterator fieldMatchIterator = fieldRe.globalMatch(structMatch.captured(2));
		QList<StructField> fields;
		while (fieldMatchIterator.hasNext()) {
			QRegularExpressionMatch fieldMatch = fieldMatchIterator.next();
			fields += StructField(fieldMatch.captured(1), fieldMatch.captured(2));
		}
		structsWithFields[structMatch.captured(1)] = fields;
	}

	return structsWithFields;
}

void Shader::addUniform(QString uniformType, QString uniformName,
							   QMap<QString, QList<StructField>> structsWithFields)
{
	bool shouldAddThis = true;

	if (structsWithFields.contains(uniformType)) {
		shouldAddThis = false;
		QList<StructField> structFields = structsWithFields[uniformType];

		for (int i = 0; i < structFields.size(); i++)
			addUniform(structFields[i].type, uniformName + "." + structFields[i].name,
									  structsWithFields);
	}

	if (!shouldAddThis)
		return;

	GLint uniformLocation = f.glGetUniformLocation(m_shaderResource->programReference(), uniformName.toLocal8Bit());
	Q_ASSERT(uniformLocation >= 0);

	m_uniformLocations[uniformName] = uniformLocation;
}

void Shader::updateUniforms(Transform &transform, Material &material, RenderingEngine &renderingEngine)
{
	Matrix4f worldMatrix = transform.transformation();
	Matrix4f projectedMatrix = renderingEngine.mainCamera().calculateViewProjection() * worldMatrix;

	for (int i = 0; i < m_uniforms.size(); i++) {
		QString uniformType = m_uniforms[i].type;
		QString uniformName = m_uniforms[i].name;

		QString renderingEnginePrefix = "R_";
		QString transformPrefix = "T_";
		QString cameraPrefix = "C_";

		if (uniformType == "sampler2D") {
			int samplerSlot = renderingEngine.samplerSlot(uniformName);
			material.findTexture(uniformName)->bind(samplerSlot);
			setUniformi(uniformName, samplerSlot);
		} else if (uniformName.startsWith(transformPrefix)) {
			if (uniformName == "T_modelViewProjection") {
				setUniform(uniformName, projectedMatrix);
			} else if (uniformName == "T_model") {
				setUniform(uniformName, worldMatrix);
			} else {
				qDebug() << uniformName;
				Q_ASSERT(false);
			}
		} else if (uniformName.startsWith(renderingEnginePrefix)) {
			QString unprefixedUniformName = uniformName.right(uniformName.size() - renderingEnginePrefix.size());

			if (uniformType == "vec3")
				setUniform(uniformName, renderingEngine.findVector3f(unprefixedUniformName));
			 else if (uniformType == "float")
				setUniformf(uniformName, renderingEngine.findFloat(unprefixedUniformName));
			 else if (uniformType == "DirectionalLight")
				setUniform(uniformName, static_cast<DirectionalLight &>(*renderingEngine.activeLight()));
			 else if (uniformType == "PointLight")
				setUniform(uniformName, static_cast<PointLight &>(*renderingEngine.activeLight()));
			 else if (uniformType == "SpotLight")
				setUniform(uniformName, static_cast<SpotLight &>(*renderingEngine.activeLight()));
			else
				renderingEngine.updateUniformStruct(transform, material, *this, uniformType, uniformName);
		} else if (uniformName.startsWith(cameraPrefix)) {
			if (uniformName == "C_eyePosition") {
				setUniform(uniformName, renderingEngine.mainCamera().transform().calculateTransformedTranslation());
			} else {
				qDebug() << uniformName;
				Q_ASSERT(false);
			}
		} else {
			if (uniformType == "vec3") {
				setUniform(uniformName, material.findVector3f(uniformName));
			} else if (uniformType == "float") {
				setUniformf(uniformName, material.findFloat(uniformName));
			}else {
				qDebug() << uniformName;
				Q_ASSERT(false);
			}
		}
	}
}

void Shader::addAllUniforms(const QString &shaderText)
{
	QMap<QString, QList<StructField>> structsWithFields = findUniformStructs(shaderText);

	QRegularExpression re("uniform (\\w*?) ([\\w]+)");
	QRegularExpressionMatchIterator i = re.globalMatch(shaderText);
	while (i.hasNext()) {
		QRegularExpressionMatch match= i.next();
		m_uniforms += Uniform(match.captured(1), match.captured(2));
		addUniform(match.captured(1), match.captured(2), structsWithFields);
	}
}

void Shader::setUniformi(const QString &uniformName, int value)
{
	f.glUniform1i(m_uniformLocations[uniformName], value);
}

void Shader::setUniformf(const QString &uniformName, float value)
{
	f.glUniform1f(m_uniformLocations[uniformName], value);
}

void Shader::setUniform(const QString &uniformName, const Vector3f &value)
{
	f.glUniform3f(m_uniformLocations[uniformName], value.x, value.y, value.z);
}

void Shader::setUniform(const QString &uniformName, const Matrix4f &value)
{
	f.glUniformMatrix4fv(m_uniformLocations[uniformName], 1, GL_TRUE, value.getM().data());
}

QString Shader::loadShader(const QString &filename)
{
	QFile shaderFile(QString(":/resources/shaders/%1").arg(filename));
	shaderFile.open(QFile::ReadOnly | QFile::Text);

	QTextStream shaderStream(&shaderFile);

	QString shaderText;
	while (!shaderStream.atEnd()) {
		QString line = shaderStream.readLine();

		QRegularExpression re("#include \"([a-z\\.]+)\"");
		QRegularExpressionMatch match = re.match(line);
		if (match.hasMatch()) {
			shaderText.append(loadShader(match.captured(1)));
		} else {
			shaderText.append(line).append("\n");
		}
	}

	shaderFile.close();

	return shaderText;
}

void Shader::setUniform(const QString &uniformName, const BaseLight &baseLight)
{
	setUniform(uniformName + ".color", baseLight.color());
	setUniformf(uniformName + ".intensity", baseLight.intensity());
}

void Shader::setUniform(const QString &uniformName, DirectionalLight &directionalLight)
{
	setUniform(uniformName + ".base", static_cast<const BaseLight &>(directionalLight));
	setUniform(uniformName + ".direction", directionalLight.direction());
}

void Shader::setUniform(const QString &uniformName, PointLight &pointLight)
{
	setUniform(uniformName + ".base", static_cast<const BaseLight &>(pointLight));
	setUniformf(uniformName + ".attenuation.constant", pointLight.attenuation().constant());
	setUniformf(uniformName + ".attenuation.linear", pointLight.attenuation().linear());
	setUniformf(uniformName + ".attenuation.exponent", pointLight.attenuation().exponent());
	setUniform(uniformName + ".position", pointLight.transform().calculateTransformedTranslation());
	setUniformf(uniformName + ".range", pointLight.range());
}

void Shader::setUniform(const QString &uniformName, SpotLight &spotLight)
{
	setUniform(uniformName + ".pointLight", static_cast<PointLight &>(spotLight));
	setUniform(uniformName + ".direction", spotLight.direction());
	setUniformf(uniformName + ".cutoff", spotLight.cutoff());
}
