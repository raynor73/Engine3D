#ifndef MESHRESOURCE_H
#define MESHRESOURCE_H

#include <QObject>
#include <engine/rendering/qopenglfunctions_selector.h>

class MeshResource : public QObject
{
	Q_OBJECT
public:
	explicit MeshResource(QObject *parent = 0);

private:
	GLuint m_vertexBufferObjectName;
	GLuint m_indexBufferObjectName;

};

#endif // MESHRESOURCE_H
