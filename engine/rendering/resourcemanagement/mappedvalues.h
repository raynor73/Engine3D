#ifndef MAPPEDVALUES_H
#define MAPPEDVALUES_H

#include <QMap>
#include <QString>
#include <engine/core/vector3f.h>

class MappedValues
{
public:
	void addVector3f(const QString &name, const Vector3f &vector) { m_vectors3f[name] = vector; }
	Vector3f findVector3f(const QString &name) const { return m_vectors3f[name]; }

	void addFloat(const QString &name, float value) { m_floats[name] = value; }
	float findFloat(const QString &name) const { return m_floats[name]; }

protected:
	QMap<QString, Vector3f> m_vectors3f;
	QMap<QString, float> m_floats;
};

#endif // MAPPEDVALUES_H
