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
#include <engine/rendering/camera.h>
#include <engine/rendering/texture.h>
#include <engine/rendering/shader.h>
#include <engine/rendering/material.h>
#include <engine/rendering/pointlight.h>
#include <engine/rendering/spotlight.h>
#include "basetutorialscene.h"

class TutorialScene : public BaseTutorialScene
{
	Q_OBJECT

public:
	TutorialScene(OpenGLWidget &, UserInput &, QObject *parent = 0);
	virtual ~TutorialScene();

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
