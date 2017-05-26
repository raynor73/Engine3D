#include "renderingengine.h"
#include <utils.h>
#include <engine/rendering/forwardambientshader.h>
#include <engine/rendering/forwarddirectionalshader.h>
#include <engine/rendering/forwardpointshader.h>
#include <engine/rendering/forwardspotshader.h>
#include <glwrapper.h>

RenderingEngine::RenderingEngine() :
	m_mainCamera(NULL)
{
	f.initializeOpenGLFunctions();

	setOpenGLFunctions(&f);

	m_samplerMap["diffuse"] = 0;
	m_vectors3f["ambient"] = Vector3f(0.1, 0.1, 0.1);

	f.glClearColor(0, 0, 0, 0);

	f.glFrontFace(GL_CW);
	f.glCullFace(GL_BACK);
	f.glEnable(GL_CULL_FACE);
	f.glEnable(GL_DEPTH_TEST);
	f.glEnable(GL_DEPTH_CLAMP);
	f.glEnable(GL_TEXTURE_2D);

	f.glGenVertexArrays(1, &m_vertexArrayName);

	m_forwardAmbientShader = new ForwardAmbientShader(f, m_vertexArrayName);
}

RenderingEngine::~RenderingEngine()
{
	delete m_forwardAmbientShader;
}

int RenderingEngine::samplerSlot(const QString &name) const
{
	return m_samplerMap[name];
}

void RenderingEngine::onOpenGLResized(GameObject &gameObject, int width, int height)
{
	gameObject.onOpenGLResized(width, height);
}

void RenderingEngine::render(GameObject &gameObject)
{
	f.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_lights.clear();
	gameObject.addToRenderingEngine(*this);

	gameObject.render(*m_forwardAmbientShader, *this);

	f.glEnable(GL_BLEND);
	f.glBlendFunc(GL_ONE, GL_ONE);
	f.glDepthMask(false);
	f.glDepthFunc(GL_EQUAL);

	for (QList<BaseLight *>::Iterator i = m_lights.begin(); i != m_lights.end(); ++i) {
		m_activeLight = (*i);
		gameObject.render(*m_activeLight->shader(), *this);
	}

	f.glDepthFunc(GL_LESS);
	f.glDepthMask(true);
	f.glDisable(GL_BLEND);
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
