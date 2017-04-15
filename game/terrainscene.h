#ifndef TERRAINSCENE_H
#define TERRAINSCENE_H

#include <engine/core/userinput.h>
#include <QTimer>
#include <engine/rendering/mesh.h>
#include <engine/rendering/material.h>
#include <engine/rendering/shader.h>
#include <game/basetutorialscene.h>
#include <game/tutorialcontroller.h>

class TerrainScene : public BaseTutorialScene
{
	Q_OBJECT

public:
	TerrainScene(UserInput &, QObject *parent = 0);
	virtual ~TerrainScene();

	virtual void makeOpenGLDependentSetup();
	virtual void render();

private:
	Mesh *m_mesh;
	Material *m_material;
	Shader *m_shader;
};

#endif // TERRAINSCENE_H
