#include <QDebug>
#include "tutorialscene.h"
#include "renderutils.h"

TutorialScene::TutorialScene(OpenGLWidget &openGLWidget, UserInput &userInput, QObject *parent) :
    Scene(parent),
    m_openGLWidget(openGLWidget),
    m_userInput(userInput)
{
    m_controller = new TutorialController(m_userInput);
    m_controller->startReadingUserInput();

    connect(&m_fpsTimer, &QTimer::timeout, [this]() {
        qDebug() << "FPS" << m_openGLWidget.fps();
    });
    m_fpsTimer.start(1000);
}

TutorialScene::~TutorialScene()
{
    m_fpsTimer.stop();
    m_controller->stopReadingUserInput();
    delete m_controller;
}

void TutorialScene::start()
{
    initializeOpenGLFunctions();
    RenderUtils::initGraphics(*this);
}

void TutorialScene::stop()
{}

void TutorialScene::render()
{
    RenderUtils::clearScreen(*this);
}
