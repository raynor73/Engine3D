#ifndef BASETUTORIALSCENE_H
#define BASETUTORIALSCENE_H

#include <engine/rendering/qopenglfunctions_selector.h>
#include "scenewithtimemeasurement.h"
#include <engine/rendering/openglwidget.h>
#include <engine/core/userinput.h>
#include "tutorialcontroller.h"
#include <engine/rendering/camera.h>
#include <engine/core/transform.h>
#include <QTimer>

class BaseTutorialScene : public SceneWithTimeMeasurement, protected QOPENGLFUNCTIONS_CLASSNAME
{
	Q_OBJECT

public:
	BaseTutorialScene(OpenGLWidget &, UserInput &, QObject *parent = 0);
	virtual ~BaseTutorialScene();

	virtual void start();
	virtual void stop();
	virtual void update(float);

protected:
	Transform *m_transform;
	Camera *m_camera;

private:
	OpenGLWidget &m_openGLWidget;
	UserInput &m_userInput;
	TutorialController *m_controller;
	QTimer m_fpsTimer;
};

#endif // BASETUTORIALSCENE_H
