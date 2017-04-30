#include "renderingengine.h"
#include <utils.h>
#include <engine/rendering/forwardambientshader.h>
#include <engine/rendering/forwarddirectionalshader.h>
#include <engine/rendering/forwardpointshader.h>
#include <engine/rendering/forwardspotshader.h>

RenderingEngine::RenderingEngine(QObject *parent) :
	QObject(parent),
	m_mainCamera(NULL),
	m_ambientLight(0.1, 0.1, 0.1)
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
	m_forwardPointShader = new ForwardPointShader(f, *this);
	m_forwarSpotShader = new ForwardSpotShader(f, *this);

	/*int lightFieldWidth = 5;
	int lightFieldDepth = 5;

	float lightFieldStartX = 0;
	float lightFieldStartY = 0;
	float lightFieldStepX = 7;
	float lightFieldStepY = 7;

	for (int i = 0; i < lightFieldWidth; i++) {
		for (int j = 0; j < lightFieldDepth; j++) {
			m_pointLights += PointLight(BaseLight(Vector3f(0, 1, 0), 0.4), Attenuation(0, 0, 1),
										Vector3f(lightFieldStartX + lightFieldStepX * i, 0,
												 lightFieldStartY + lightFieldStepY * j),
										100);
		}
	}*/
}

RenderingEngine::~RenderingEngine()
{
	if (m_mainCamera != NULL)
		delete m_mainCamera;

	delete m_forwarSpotShader;
	delete m_forwardPointShader;
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

	m_lights.clear();
	gameObject.addToRenderingEngine(*this);

	gameObject.render(*m_mainCamera, *m_forwardAmbientShader);

	f.glEnable(GL_BLEND);
	f.glBlendFunc(GL_ONE, GL_ONE);
	f.glDepthMask(false);
	f.glDepthFunc(GL_EQUAL);

	for (QList<BaseLight *>::Iterator i = m_lights.begin(); i != m_lights.end(); ++i) {
		m_activeLight = (*i);
		gameObject.render(*m_mainCamera, *m_activeLight->shader());
	}

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
