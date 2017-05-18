#include <QVector>
#include <QFile>
#include <QTextStream>
#include <engine/rendering/meshloading/objmodel.h>
#include <engine/rendering/meshloading/indexedmodel.h>
#include "mesh.h"

Mesh::Mesh(QOPENGLFUNCTIONS_CLASSNAME &f, const QString &filename, bool shouldCalculateNormals, QObject *parent) :
	QObject(parent),
	f(f),
	m_numberOfIndices(0),
	m_temporaryVertexBuffer(NULL)
{
	f.glGenBuffers(1, &m_vertexBufferObjectName);
	f.glGenBuffers(1, &m_indexBufferObjectName);

	loadMesh(filename, shouldCalculateNormals);
}

Mesh::Mesh(QOPENGLFUNCTIONS_CLASSNAME &f, const QString &filename, QObject *parent) : Mesh(f, filename, false, parent)
{}

Mesh::Mesh(QOPENGLFUNCTIONS_CLASSNAME &f, QObject *parent) :
	QObject(parent),
	f(f),
	m_numberOfIndices(0),
	m_temporaryVertexBuffer(NULL)
{
	f.glGenBuffers(1, &m_vertexBufferObjectName);
	f.glGenBuffers(1, &m_indexBufferObjectName);
}

Mesh::~Mesh()
{
	f.glDeleteBuffers(1, &m_vertexBufferObjectName);
	f.glDeleteBuffers(1, &m_indexBufferObjectName);
	if (m_temporaryVertexBuffer != NULL) {
		delete m_temporaryVertexBuffer;
		m_temporaryVertexBuffer = NULL;
	}
}

void Mesh::setVertices(QList<Vertex> &vertices, const QVector<unsigned int> &indices)
{
	setVertices(vertices, indices, false);
}

void Mesh::setVertices(QList<Vertex> &vertices, const QVector<unsigned int> &indices, bool shouldCalculateNormals)
{
	if (shouldCalculateNormals)
		calculateNormals(vertices, indices);

	if (m_temporaryVertexBuffer != NULL)
		delete m_temporaryVertexBuffer;

	m_numberOfIndices = indices.size();

	auto numberOfVertices = vertices.size();

	auto sizeOfVertexBuffer = numberOfVertices * Vertex::SIZE * sizeof(float);
	m_temporaryVertexBuffer = new unsigned char[sizeOfVertexBuffer];
	auto m_floatBuffer = reinterpret_cast<float *>(m_temporaryVertexBuffer);
	for (int i = 0; i < numberOfVertices; i++) {
		int base = i * Vertex::SIZE;
		const Vector3f &position = vertices.at(i).position;
		const Vector2f &textureCoordinate = vertices.at(i).textureCoordinate;
		const Vector3f &normal = vertices.at(i).normal;

		m_floatBuffer[base] = position.x;
		m_floatBuffer[base + 1] = position.y;
		m_floatBuffer[base + 2] = position.z;
		m_floatBuffer[base + 3] = textureCoordinate.x;
		m_floatBuffer[base + 4] = textureCoordinate.y;
		m_floatBuffer[base + 5] = normal.x;
		m_floatBuffer[base + 6] = normal.y;
		m_floatBuffer[base + 7] = normal.z;
	}

	f.glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjectName);
	f.glBufferData(GL_ARRAY_BUFFER, sizeOfVertexBuffer, m_temporaryVertexBuffer, GL_STATIC_DRAW);

	f.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObjectName);
	f.glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numberOfIndices * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void Mesh::draw()
{
	f.glEnableVertexAttribArray(0);
	f.glEnableVertexAttribArray(1);
	f.glEnableVertexAttribArray(2);

	f.glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjectName);
	f.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * sizeof(float), 0);
	f.glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, Vertex::SIZE * sizeof(float),
							reinterpret_cast<const void *>(3 * sizeof(float)));
	f.glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * sizeof(float),
							reinterpret_cast<const void *>(5 * sizeof(float)));

	f.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObjectName);

	f.glDrawElements(GL_TRIANGLES, m_numberOfIndices, GL_UNSIGNED_INT, 0);

	f.glDisableVertexAttribArray(0);
	f.glDisableVertexAttribArray(1);
	f.glDisableVertexAttribArray(2);
}

void Mesh::calculateNormals(QList<Vertex> &vertices, const QVector<unsigned int> &indices)
{
	for (int i = 0; i < indices.size(); i += 3) {
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		Vector3f v1 = vertices.at(i1).position - vertices.at(i0).position;
		Vector3f v2 = vertices.at(i2).position  -vertices.at(i0).position;

		Vector3f normal = v1.cross(v2).normalized();

		vertices[i0].normal += normal;
		vertices[i1].normal += normal;
		vertices[i2].normal += normal;
	}

	for (int i = 0; i < vertices.size(); i++)
		vertices[i].normal = vertices[i].normal.normalized();
}

void Mesh::loadMesh(const QString &filename, bool shouldCalculateNormals)
{
	OBJModel objModel(filename);
	IndexedModel indexedModel = objModel.toIndexedModel();
	if (shouldCalculateNormals)
		indexedModel.calculateNormals();

	QList<Vertex> vertices;
	QVector<unsigned int> indices;

	for (int i = 0; i < indexedModel.positions().size(); i++)
		vertices += Vertex(indexedModel.positions()[i], indexedModel.textureCoordinates()[i],
						   indexedModel.normals()[i]);

	for (int i = 0; i < indexedModel.indices().size(); i++)
		indices += indexedModel.indices()[i];

	setVertices(vertices, indices, false);

	/*QFile meshFile(QString(":/resources/models/%1").arg(filename));
	meshFile.open(QFile::ReadOnly | QFile::Text);
	QList<Vertex> vertices;
	QVector<unsigned int> indices;

	QTextStream meshStream(&meshFile);

	while (!meshStream.atEnd()) {
		auto line = meshStream.readLine();
		auto tokens = line.split(' ');

		if (tokens.size() == 4) {
			if (tokens.at(0) == "v") {
				auto x = tokens.at(1).toFloat();
				auto y = tokens.at(2).toFloat();
				auto z = tokens.at(3).toFloat();
				vertices += Vertex(Vector3f(x, y, z));
			} else if (tokens.at(0) == "f") {
				for (int i = 1; i <= 3; i++)
					indices += tokens.at(i).toInt() - 1;
			}
		}
	}

	meshFile.close();

	setVertices(vertices, indices, shouldCalculateNormals);*/
}
