#ifndef BASETUTORIALSCENE_H
#define BASETUTORIALSCENE_H

#include <engine/rendering/qopenglfunctions_selector.h>
#include <engine/core/scenewithtimemeasurement.h>
#include <engine/rendering/openglwidget.h>
#include <engine/core/userinput.h>
#include <game/tutorialcontroller.h>
#include <engine/rendering/camera.h>
#include <engine/core/transform.h>
#include <QTimer>

class BaseTutorialScene : public SceneWithTimeMeasurement
{
	Q_OBJECT

public:
	BaseTutorialScene(UserInput &, QObject *parent = 0);
	virtual ~BaseTutorialScene();

	virtual void makeOpenGLDependentSetup();
	virtual void onOpenGLResized(int, int);
	virtual void start();
	virtual void stop();
	virtual void update(float);
	virtual void render();

protected:
	QOPENGLFUNCTIONS_CLASSNAME *m_openGLFunctions;
	Transform *m_transform;
	Camera *m_camera;

private:
	UserInput &m_userInput;
	TutorialController *m_controller;
	QTimer m_fpsTimer;
	int m_fpsCounter;
};

#endif // BASETUTORIALSCENE_H
