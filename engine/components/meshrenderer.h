#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <engine/components/gamecomponent.h>
#include <engine/rendering/mesh.h>
#include <engine/rendering/material.h>
#include <engine/rendering/shader.h>

class MeshRenderer : public GameComponent
{
	Q_OBJECT

public:
	MeshRenderer(Mesh *mesh, Material *material, QObject *parent = 0);

	void render(Camera &, Shader &shader) override;

private:
	Mesh *m_mesh;
	Material *m_material;
};

#endif // MESHRENDERER_H
