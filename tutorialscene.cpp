#include "tutorialscene.h"

TutorialScene::TutorialScene(UserInput &userInput, QObject *parent) :
    Scene(parent),
    m_userInput(userInput)
{}

void TutorialScene::start()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 1, 1);
}

void TutorialScene::stop()
{}

void TutorialScene::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
