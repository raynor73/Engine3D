#include "meshrenderer.h"
#include <engine/rendering/renderingengine.h>

MeshRenderer::MeshRenderer(Mesh *mesh, Material *material, QObject *parent) :
	GameComponent(parent),
	m_mesh(mesh),
	m_material(material)
{
	Q_ASSERT(m_mesh != NULL);
	Q_ASSERT(m_material != NULL);
}

void MeshRenderer::render(Shader &shader, RenderingEngine &renderingEngine)
{
	shader.bind();
	shader.updateUniforms(transform(), *m_material, renderingEngine);
	m_mesh->draw();
}
