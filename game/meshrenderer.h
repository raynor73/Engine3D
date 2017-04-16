#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <engine/core/gamecomponent.h>
#include <engine/rendering/mesh.h>
#include <engine/rendering/material.h>
#include <engine/rendering/basicshader.h>

class MeshRenderer : public GameComponent
{
	Q_OBJECT

public:
	MeshRenderer(QOPENGLFUNCTIONS_CLASSNAME &, Mesh *, Material *, QObject *parent = 0);

	virtual void render(Transform &);

private:
	Mesh *m_mesh;
	Material *m_material;
	BasicShader m_shader;
};

#endif // MESHRENDERER_H
