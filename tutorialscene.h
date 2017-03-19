#ifndef TUTORIALSCENE_H
#define TUTORIALSCENE_H

#include <QObject>
#include <QOpenGLFunctions>
#include "scene.h"
#include "userinput.h"

class TutorialScene : public Scene, protected QOpenGLFunctions
{
public:
    explicit TutorialScene(UserInput &, QObject *parent = 0);

    virtual void start();
    virtual void stop();
    virtual void render();

private:
    UserInput &m_userInput;
};

#endif // TUTORIALSCENE_H
