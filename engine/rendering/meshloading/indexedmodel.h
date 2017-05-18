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
	IndexedModel(const IndexedModel &);

	IndexedModel &operator =(const IndexedModel &);

	void calculateNormals();

	QList<Vector3f> &positions() { return m_positions; }
	QList<Vector2f> &textureCoordinates() { return m_textureCoordinates; }
	QList<Vector3f> &normals()  { return m_normals; }
	QList<int> &indices() { return m_indices; }

private:
	QList<Vector3f> m_positions;
	QList<Vector2f> m_textureCoordinates;
	QList<Vector3f> m_normals;
	QList<int> m_indices;
};

#endif // INDEXEDMODEL_H
