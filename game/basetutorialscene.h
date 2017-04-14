#ifndef BASETUTORIALSCENE_H
#define BASETUTORIALSCENE_H

#include <engine/rendering/qopenglfunctions_selector.h>
#include <game/scenewithtimemeasurement.h>
#include <engine/rendering/openglwidget.h>
#include <engine/core/userinput.h>
#include <game/tutorialcontroller.h>
#include <engine/rendering/camera.h>
#include <engine/core/transform.h>
#include <engine/core/coreengine.h>
#include <QTimer>

class BaseTutorialScene : public SceneWithTimeMeasurement, protected QOPENGLFUNCTIONS_CLASSNAME
{
	Q_OBJECT

public:
	BaseTutorialScene(CoreEngine &, UserInput &, QObject *parent = 0);
	virtual ~BaseTutorialScene();

	virtual void makeOpenGLDependentSetup();
	virtual void onOpenGLResized(int, int);
	virtual void start();
	virtual void stop();
	virtual void update(float);

protected:
	Transform *m_transform;
	Camera *m_camera;

private:
	CoreEngine &m_coreEngine;
	UserInput &m_userInput;
	TutorialController *m_controller;
	QTimer m_fpsTimer;
};

#endif // BASETUTORIALSCENE_H
