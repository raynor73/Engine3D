#ifndef TERRAINSCENE_H
#define TERRAINSCENE_H

#include "scenewithtimemeasurement.h"
#include <engine/rendering/qopenglfunctions_selector.h>
#include <engine/rendering/openglwidget.h>
#include <engine/core/userinput.h>
#include "tutorialcontroller.h"
#include <engine/rendering/camera.h>
#include <QTimer>
#include <engine/rendering/mesh.h>
#include <engine/rendering/material.h>
#include <engine/rendering/shader.h>
#include <engine/core/transform.h>
#include "tutorialcontroller.h"

class TerrainScene : public SceneWithTimeMeasurement, protected QOPENGLFUNCTIONS_CLASSNAME
{
	Q_OBJECT

public:
	TerrainScene(OpenGLWidget &, UserInput &, QObject *parent = 0);
	virtual ~TerrainScene();

	virtual void start();
	virtual void stop();
	virtual void render();

	virtual void update(float);

private:
	OpenGLWidget &m_openGLWidget;
	UserInput &m_userInput;
	QTimer m_fpsTimer;
	TutorialController *m_controller;
	Mesh *m_mesh;
	Material *m_material;
	Shader *m_shader;
	Transform *m_transform;
	Camera *m_camera;
};

#endif // TERRAINSCENE_H
