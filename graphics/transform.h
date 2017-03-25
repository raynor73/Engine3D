#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QObject>
#include "geometry/vector3f.h"
#include "geometry/matrix4f.h"

class Transform : public QObject
{
	Q_OBJECT
public:
	explicit Transform(QObject *parent = 0);

	Vector3f *translation() { return &m_translation; }
	void setTranslation(const Vector3f &);
	void setTranslation(float, float, float);
	Matrix4f transformation();

private:
	Vector3f m_translation;
};

#endif // TRANSFORM_H
