#ifndef INDEXEDMODEL_H
#define INDEXEDMODEL_H

#include <QObject>
#include <engine/core/vector3f.h>
#include <engine/core/vector2f.h>
#include <QList>

class IndexedModel : public QObject
{
	Q_OBJECT
public:
	explicit IndexedModel(QObject *parent = 0);

	const QList<Vector3f> &vertices() const { return m_vertices; }
	const QList<Vector2f> &textureCoordinates() const { return m_textureCoordinates; }
	const QList<Vector3f> &normals() const { return m_normals; }
	const QList<int> &indices() const { return m_indices; }

private:
	QList<Vector3f> m_vertices;
	QList<Vector2f> m_textureCoordinates;
	QList<Vector3f> m_normals;
	QList<int> m_indices;
};

#endif // INDEXEDMODEL_H
