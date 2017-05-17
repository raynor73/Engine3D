#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <QObject>
#include <engine/rendering/meshloading/objindex.h>
#include <engine/core/vector3f.h>

class OBJModel : public QObject
{
	Q_OBJECT
public:
	explicit OBJModel(QObject *parent = 0);

	const QList<Vector3f> &vertices() const { return m_vertices; }
	const QList<Vector2f> &textureCoordinates() const { return m_textureCoordinates; }
	const QList<Vector3f> &normals() const { return m_normals; }
	const QList<OBJIndex> &indices() const { return m_indices; }

private:
	QList<Vector3f> m_vertices;
	QList<Vector2f> m_textureCoordinates;
	QList<Vector3f> m_normals;
	QList<OBJIndex> m_indices;
};

#endif // OBJMODEL_H
