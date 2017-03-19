#ifndef TUTORIALSCENE_H
#define TUTORIALSCENE_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QTimer>
#include "scene.h"
#include "userinput.h"
#include "tutorialcontroller.h"
#include "openglwidget.h"

class TutorialScene : public Scene, protected QOpenGLFunctions
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
};

#endif // TUTORIALSCENE_H
