#ifndef TUTORIALSCENE_H
#define TUTORIALSCENE_H

#include <QObject>
#include "qopenglfunctions_selector.h"
#include <QTimer>
#include <QElapsedTimer>
#include "graphics/mesh.h"
#include "userinput.h"
#include "tutorialcontroller.h"
#include "openglwidget.h"
#include "graphics/transform.h"
#include "graphics/camera.h"
#include "graphics/texture.h"
#include <graphics/shader.h>
#include <graphics/material.h>
#include <graphics/pointlight.h>
#include <graphics/spotlight.h>
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
