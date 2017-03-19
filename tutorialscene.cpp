#include <QDebug>
#include "tutorialscene.h"
#include "geometry/vector2f.h"

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

    Vector2f v(10000.234f, 5.6789f);
    qDebug() << v;
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
    glClearColor(0, 0, 1, 1);
}

void TutorialScene::stop()
{}

void TutorialScene::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
