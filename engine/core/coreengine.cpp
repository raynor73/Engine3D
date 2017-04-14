#include "coreengine.h"
#include <QSurfaceFormat>
#include <engine/rendering/mainwindow.h>

CoreEngine::CoreEngine(int width, int height, float maxFps, const QString &title, QObject *parent) :
	QObject(parent),
	m_scene(NULL),
	m_isOpenGLReady(false),
	m_isOpenGLSizeKnown(false)
{
	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	format.setVersion(3, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(format);

	m_mainWindow = new MainWindow(width, height, maxFps);
	m_mainWindow->setWindowTitle(title);

	connect(m_mainWindow->openGLWidget(), &OpenGLWidget::openGLReady, this, &CoreEngine::onOpenGLReady);
	connect(m_mainWindow->openGLWidget(), &OpenGLWidget::openGLResized, this, &CoreEngine::onOpenGLResized);
	connect(m_mainWindow->openGLWidget(), &OpenGLWidget::render, this, &CoreEngine::onRender);

	m_mainWindow->show();
}

CoreEngine::~CoreEngine()
{
	disconnect(m_mainWindow->openGLWidget(), &OpenGLWidget::openGLReady, this, &CoreEngine::onOpenGLReady);
	disconnect(m_mainWindow->openGLWidget(), &OpenGLWidget::openGLResized, this, &CoreEngine::onOpenGLResized);
	disconnect(m_mainWindow->openGLWidget(), &OpenGLWidget::render, this, &CoreEngine::onRender);
}

void CoreEngine::setScene(Scene *scene)
{
	m_scene = scene;

	if (m_isOpenGLReady)
		m_scene->makeOpenGLDependentSetup();

	if (m_isOpenGLSizeKnown)
		m_scene->onOpenGLResized(m_openGLWidth, m_openGLHeight);
}

void CoreEngine::onOpenGLReady()
{
	m_isOpenGLReady = true;

	if (m_scene != NULL)
		m_scene->makeOpenGLDependentSetup();
}

void CoreEngine::onOpenGLResized(int width, int height)
{
	m_isOpenGLSizeKnown = true;
	m_openGLWidth = width;
	m_openGLHeight = height;

	if (m_scene != NULL)
		m_scene->onOpenGLResized(m_openGLWidth, m_openGLHeight);
}

void CoreEngine::onRender()
{
	if (m_scene != NULL) {
		m_scene->update();
		m_scene->render();
	}
}
