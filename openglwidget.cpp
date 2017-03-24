#include <QTimer>
#include <QDebug>
#include "openglwidget.h"
#include "defaultscene.h"

OpenGLWidget::OpenGLWidget(QWidget *parent, float fpsLimit) :
	QOpenGLWidget(parent),
	m_fpsPeriod(1000 / fpsLimit),
	m_scene(NULL),
	m_isOpenGLReadySignalEmitted(false)
{}

void OpenGLWidget::setScene(Scene *scene)
{
	m_scene = scene;
}

void OpenGLWidget::initializeGL() {}

void OpenGLWidget::resizeGL(int, int) {}

void OpenGLWidget::paintGL()
{
	if (!m_isOpenGLReadySignalEmitted) {
		emit openGLReady();
		m_isOpenGLReadySignalEmitted = true;
	}

	if (m_fpsTimer.isValid())
		m_fps = 1000.0f / m_fpsTimer.elapsed();
	m_fpsTimer.start();

	m_renderTimer.start();

	if (m_scene != NULL) {
		m_scene->update();
		m_scene->render();
	}

	int delay = m_fpsPeriod - m_renderTimer.elapsed();
	QTimer::singleShot(delay > 0 ? delay : 1, this, SLOT(update()));
}
