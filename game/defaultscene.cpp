#include "defaultscene.h"

DefaultScene::DefaultScene(QObject *parent) : Scene(parent)
{}

void DefaultScene::start()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
}

void DefaultScene::stop()
{}

void DefaultScene::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
