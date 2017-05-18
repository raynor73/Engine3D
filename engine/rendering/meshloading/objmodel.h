#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <QObject>
#include <engine/rendering/meshloading/objindex.h>
#include <engine/rendering/meshloading/indexedmodel.h>
#include <engine/core/vector3f.h>

class QString;
class OBJModel : public QObject
{
	Q_OBJECT
public:
	OBJModel(const QString &filename, QObject *parent = 0);

	IndexedModel toIndexedModel() const;

private:
	QList<Vector3f> m_positions;
	QList<Vector2f> m_textureCoordinates;
	QList<Vector3f> m_normals;
	QList<OBJIndex> m_indices;
	bool m_hasTextureCoordinates;
	bool m_hasNormals;

	OBJIndex parseOBJIndex(const QString &);
};

#endif // OBJMODEL_H
