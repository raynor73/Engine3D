#ifndef TUTORIALSCENE_H
#define TUTORIALSCENE_H

#include <QObject>
#include "qopenglfunctions_selector.h"
#include <QTimer>
#include "scene.h"
#include "geometry/mesh.h"
#include "userinput.h"
#include "tutorialcontroller.h"
#include "openglwidget.h"
#include "graphics/shader.h"

class TutorialScene : public Scene, protected QOPENGLFUNCTIONS_CLASSNAME
{
public:
    explicit TutorialScene(OpenGLWidget &, UserInput &, QObject *parent = 0);
    ~TutorialScene();

    virtual void start();
    virtual void stop();
    virtual void render();

private:
    OpenGLWidget &m_openGLWidget;
    UserInput &m_userInput;
    TutorialController *m_controller;
    QTimer m_fpsTimer;
	Mesh *m_mesh;
	Shader *m_shader;
};

#endif // TUTORIALSCENE_H
