#include "renderingengine.h"
#include <utils.h>
#include <engine/rendering/forwardambientshader.h>
#include <engine/rendering/forwarddirectionalshader.h>

RenderingEngine::RenderingEngine(QObject *parent) :
	QObject(parent),
	m_mainCamera(NULL),
	m_ambientLight(0.2, 0.2, 0.2),
	m_directionalLight(BaseLight(Vector3f(0, 0, 1), 0.4), Vector3f(1, 1, 1)),
	m_directionalLight2(BaseLight(Vector3f(1, 0, 0), 0.4), Vector3f(-1, 1, -1))
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

	m_forwardAmbientShader = new ForwardAmbientShader(f, *this);
	m_forwardDirectionalShader = new ForwardDirectionalShader(f, *this);
}

RenderingEngine::~RenderingEngine()
{
	if (m_mainCamera != NULL)
		delete m_mainCamera;

	delete m_forwardDirectionalShader;
	delete m_forwardAmbientShader;
}

void RenderingEngine::onOpenGLResized(GameObject &gameObject, int width, int height)
{
	m_mainCamera = new Camera(Utils::toRadians(70), float(width) / float(height), 0.01, 1000);
	gameObject.onOpenGLResized(width, height);
}

void RenderingEngine::render(GameObject &gameObject)
{
	clearScreen();

	gameObject.render(*m_mainCamera, *m_forwardAmbientShader);

	f.glEnable(GL_BLEND);
	f.glBlendFunc(GL_ONE, GL_ONE);
	f.glDepthMask(false);
	f.glDepthFunc(GL_EQUAL);

	gameObject.render(*m_mainCamera, *m_forwardDirectionalShader);

	DirectionalLight tmp = m_directionalLight;
	m_directionalLight = m_directionalLight2;

	gameObject.render(*m_mainCamera, *m_forwardDirectionalShader);

	m_directionalLight = tmp;

	f.glDepthFunc(GL_LESS);
	f.glDepthMask(true);
	f.glDisable(GL_BLEND);
}

void RenderingEngine::clearScreen()
{
	// TODO: Stencil buffer
	f.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderingEngine::setClearColor(QOPENGLFUNCTIONS_CLASSNAME &f, const Vector3f &color)
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
