#include "meshrenderer.h"

MeshRenderer::MeshRenderer(Mesh *mesh, Material *material, QObject *parent) :
	GameComponent(parent),
	m_mesh(mesh),
	m_material(material)
{
	Q_ASSERT(m_mesh != NULL);
	Q_ASSERT(m_material != NULL);
}

void MeshRenderer::render(Transform &transform, Shader &shader)
{
	shader.bind();
	shader.updateUniforms(transform, *m_material);
	m_mesh->draw();
}
