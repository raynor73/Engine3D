#include "defaultscene.h"

DefaultScene::DefaultScene(QObject *parent) :
    Scene(parent),
    m_openGLFunctions(QOpenGLContext::currentContext()->functions())
{}

void DefaultScene::start()
{
    m_openGLFunctions->glClearColor(0, 0, 0, 1);
}

void DefaultScene::stop()
{}

void DefaultScene::render()
{
    m_openGLFunctions->glClear(GL_COLOR_BUFFER_BIT);
}
