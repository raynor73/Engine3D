#include <QTimer>
#include <QDebug>
#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent, float fpsLimit) :
    QOpenGLWidget(parent),
    m_fpsPeriod(1000 / fpsLimit)
{}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
}

void OpenGLWidget::resizeGL(int, int) {}

void OpenGLWidget::paintGL()
{
    if (m_fpsTimer.isValid())
        m_fps = 1000.0f / m_fpsTimer.elapsed();
    m_fpsTimer.start();

    m_renderTimer.start();

    doRender();

    int delay = m_fpsPeriod - m_renderTimer.elapsed();
    QTimer::singleShot(delay > 0 ? delay : 1, this, SLOT(update()));
}

void OpenGLWidget::doRender()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
