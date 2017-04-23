#include "renderingengine.h"
#include <utils.h>

RenderingEngine::RenderingEngine(QObject *parent) :
	QObject(parent),
	m_mainCamera(NULL)
{
	f.initializeOpenGLFunctions();

	f.glClearColor(0, 0, 0, 0);

	f.glFrontFace(GL_CW);
	f.glCullFace(GL_BACK);
	f.glEnable(GL_CULL_FACE);
	f.glEnable(GL_DEPTH_TEST);
	f.glEnable(GL_DEPTH_CLAMP);
	f.glEnable(GL_TEXTURE_2D);

	GLuint vertexArrayName;
	f.glGenVertexArrays(1, &vertexArrayName);
	f.glBindVertexArray(vertexArrayName);

	m_basicShader = new BasicShader(f);
}

RenderingEngine::~RenderingEngine()
{
	if (m_mainCamera != NULL)
		delete m_mainCamera;

	delete m_basicShader;
}

void RenderingEngine::onOpenGLResized(GameObject &gameObject, int width, int height)
{
	m_mainCamera = new Camera(Utils::toRadians(70), float(width) / float(height), 0.01, 1000);
	gameObject.onOpenGLResized(width, height);
}

void RenderingEngine::render(GameObject &gameObject)
{
	clearScreen();
	m_basicShader->setRenderingEngine(this);
	gameObject.render(*m_basicShader);
}

void RenderingEngine::clearScreen()
{
	// TODO: Stencil buffer
	f.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderingEngine::setClearColor(QOPENGLFUNCTIONS_CLASSNAME &f,const Vector3f &color)
{
	f.glClearColor(color.x, color.y, color.z, 1);
}

void RenderingEngine::enableTextures(QOPENGLFUNCTIONS_CLASSNAME &f, bool isEnabled)
{
	if (isEnabled)
		f.glEnable(GL_TEXTURE_2D);
	else
		f.glDisable(GL_TEXTURE_2D);
}

QString RenderingEngine::getOpenGLVersion(QOPENGLFUNCTIONS_CLASSNAME &f)
{
	return QString::fromLocal8Bit(reinterpret_cast<const char *>(f.glGetString(GL_VERSION)));
}

void RenderingEngine::unbindTextures(QOPENGLFUNCTIONS_CLASSNAME &f)
{
	f.glBindTexture(GL_TEXTURE_2D, 0);
}
