#ifndef TUTORIALSCENEMONKEY_H
#define TUTORIALSCENEMONKEY_H

#include "basetutorialscene.h"
#include <engine/rendering/mesh.h>
#include <engine/rendering/texture.h>
#include <engine/rendering/material.h>
#include <engine/rendering/shader.h>

class TutorialSceneMonkey : public BaseTutorialScene
{
	Q_OBJECT
public:
	TutorialSceneMonkey(OpenGLWidget &, UserInput &, QObject *parent = 0);
	virtual ~TutorialSceneMonkey();

	virtual void update(float);
	virtual void render();

private:
	Mesh *m_mesh;
	Material *m_material;
	Shader *m_shader;
};

#endif // TUTORIALSCENEMONKEY_H
