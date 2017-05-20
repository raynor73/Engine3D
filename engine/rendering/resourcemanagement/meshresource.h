#ifndef MESHRESOURCE_H
#define MESHRESOURCE_H

#include <QObject>
#include <glwrapper.h>

class MeshResource : public QObject
{
	Q_OBJECT
public:
	explicit MeshResource(QObject *parent = 0);
	~MeshResource();

	GLuint vertexBufferObjectName() const { return m_vertexBufferObjectName; }
	GLuint indexBufferObjectName() const { return m_indexBufferObjectName; }

	int numberOfIndices() const { return m_numberOfIndices; }
	void setNumberOfIndices(int numberOfIndices) { m_numberOfIndices = numberOfIndices; }

private:
	GLuint m_vertexBufferObjectName;
	GLuint m_indexBufferObjectName;
	int m_numberOfIndices;
};

#endif // MESHRESOURCE_H
