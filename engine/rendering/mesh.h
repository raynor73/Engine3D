#ifndef MESH_H
#define MESH_H

#include <QObject>
#include <engine/rendering/qopenglfunctions_selector.h>
#include <QList>
#include <QMap>
#include <engine/rendering/vertex.h>
#include <engine/rendering/resourcemanagement/meshresource.h>
#include <QSharedPointer>
#include <QWeakPointer>

class Mesh : public QObject
{
	Q_OBJECT
public:
	Mesh(QOPENGLFUNCTIONS_CLASSNAME &, QObject *parent = 0);
	Mesh(QOPENGLFUNCTIONS_CLASSNAME &, const QString &filename, QObject *parent = 0);
	~Mesh();

	void setVertices(QList<Vertex> &, const QVector<unsigned int> &);
	void setVertices(QList<Vertex> &, const QVector<unsigned int> &, bool);
	void draw();

private:
	static QMap<QString, QWeakPointer<MeshResource>> s_loadedModels;

	QOPENGLFUNCTIONS_CLASSNAME &f;

	QSharedPointer<MeshResource> m_meshResource;
	unsigned char *m_temporaryVertexBuffer;

	void loadMesh(const QString &filename);
	void calculateNormals(QList<Vertex> &, const QVector<unsigned int> &);
	void loadMeshAndPutToCache(const QString &filename);
};

#endif // MESH_H
