#ifndef TUTORIALSCENE_H
#define TUTORIALSCENE_H

#include <QObject>
#include "qopenglfunctions_selector.h"
#include <QTimer>
#include <QElapsedTimer>
#include "scene.h"
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

class TutorialScene : public Scene, protected QOPENGLFUNCTIONS_CLASSNAME
{
public:
	explicit TutorialScene(OpenGLWidget &, UserInput &, QObject *parent = 0);
	~TutorialScene();

	virtual void start();
	virtual void stop();
	virtual void update();
	virtual void render();

private:
	OpenGLWidget &m_openGLWidget;
	UserInput &m_userInput;
	TutorialController *m_controller;
	QTimer m_fpsTimer;
	QElapsedTimer m_deltaTimer;
	Mesh *m_mesh;
	Material *m_material;
	Shader *m_shader;
	Transform *m_transform;
	Camera *m_camera;
	QList<PointLight *> m_pointLights;
};

#endif // TUTORIALSCENE_H
