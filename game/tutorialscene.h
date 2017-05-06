#ifndef TUTORIALSCENE_H
#define TUTORIALSCENE_H

#include <QObject>
#include <engine/rendering/qopenglfunctions_selector.h>
#include <QTimer>
#include <QElapsedTimer>
#include <engine/rendering/mesh.h>
#include <engine/core/userinput.h>
#include "tutorialcontroller.h"
#include <engine/rendering/openglwidget.h>
#include <engine/core/transform.h>
#include <engine/components/camera.h>
#include <engine/rendering/texture.h>
#include <engine/rendering/shader.h>
#include <engine/rendering/material.h>
#include <engine/components/pointlight.h>
#include <engine/components/spotlight.h>
#include <game/basetutorialscene.h>

class TutorialScene : public BaseTutorialScene
{
	Q_OBJECT

public:
	TutorialScene(UserInput &, QObject *parent = 0);
	virtual ~TutorialScene();

	virtual void makeOpenGLDependentSetup();
	virtual void update(float);
	virtual void render();

private:
	Mesh *m_mesh;
	Texture *m_texture;
	Material *m_material;
	Shader *m_shader;
	QList<PointLight *> m_pointLights;
	QList<SpotLight *> m_spotLights;
};

#endif // TUTORIALSCENE_H
