#include "coreengine.h"
#include <QSurfaceFormat>
#include <engine/rendering/mainwindow.h>

CoreEngine::CoreEngine(int width, int height, float maxFps, const QString &title, QObject *parent) :
	QObject(parent),
	m_scene(NULL),
	m_isOpenGLReady(false)
{
	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	format.setVersion(3, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(format);

	MainWindow w(width, height, maxFps);

	w.setWindowTitle(title);

	connect(this, &CoreEngine::onOpenGLReady, w.openGLWidget(), &OpenGLWidget::openGLReady);

	w.show();
}

CoreEngine::~CoreEngine()
{
	disconnect(this, &CoreEngine::onOpenGLReady, w.openGLWidget(), &OpenGLWidget::openGLReady);
}

void CoreEngine::setScene(Scene *scene)
{
	m_scene = scene;

	//connect(m_scene, Sc)
}

CoreEngine::onOpenGLReady()
{
	m_isOpenGLReady = true;
	if (m_scene != NULL)
		m_scene->makeOpenGLDependentSetup();
}
