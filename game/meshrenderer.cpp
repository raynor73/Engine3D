#include "meshrenderer.h"

MeshRenderer::MeshRenderer(QOPENGLFUNCTIONS_CLASSNAME &f, Mesh *mesh, Material *material, QObject *parent) :
	GameComponent(parent),
	m_mesh(mesh),
	m_material(material),
	m_shader(f)
{}

void MeshRenderer::render(Transform &transform)
{
	m_shader.bind();
	m_shader.updateUniforms(transform.transformation(), transform.projectedTransformation(), *m_material);
	m_mesh->draw();
}
