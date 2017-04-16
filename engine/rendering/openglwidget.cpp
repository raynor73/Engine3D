#include <QTimer>
#include <engine/rendering/openglwidget.h>

OpenGLWidget::OpenGLWidget(QWidget *parent, float maxFps) :
	QOpenGLWidget(parent),
	m_fpsPeriod(1000 / maxFps)
{}

void OpenGLWidget::initializeGL()
{
	emit openGLReady();
}

void OpenGLWidget::resizeGL(int width, int height)
{
	emit openGLResized(width, height);
}

void OpenGLWidget::paintGL()
{
	if (m_fpsTimer.isValid())
		m_fps = 1000.0f / m_fpsTimer.elapsed();
	m_fpsTimer.start();

	m_renderTimer.start();

	emit render();

	int delay = m_fpsPeriod - m_renderTimer.elapsed();
	QTimer::singleShot(delay > 0 ? delay : 1, this, SLOT(update()));
}
