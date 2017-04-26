#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include <QObject>
#include <engine/rendering/camera.h>
#include <engine/core/gameobject.h>
#include <engine/rendering/qopenglfunctions_selector.h>
#include <engine/rendering/directionallight.h>
#include <engine/rendering/pointlight.h>

class ForwardAmbientShader;
class ForwardDirectionalShader;
class ForwardPointShader;
class RenderingEngine : public QObject
{
	Q_OBJECT
public:
	explicit RenderingEngine(QObject *parent = 0);
	virtual ~RenderingEngine();

	void onOpenGLResized(GameObject &gameObject, int width, int height);
	void render(GameObject &gameObject);
	Camera &mainCamera() const { Q_ASSERT(m_mainCamera != NULL); return *m_mainCamera; }
	Vector3f &ambientLight() { return m_ambientLight; }
	DirectionalLight &directionalLight() { return m_directionalLight; }
	PointLight &pointLight() { return m_pointLight; }

private:
	QOPENGLFUNCTIONS_CLASSNAME f;
	Camera *m_mainCamera;
	ForwardAmbientShader *m_forwardAmbientShader;
	ForwardDirectionalShader *m_forwardDirectionalShader;
	ForwardPointShader *m_forwardPointShader;
	Vector3f m_ambientLight;
	DirectionalLight m_directionalLight;
	DirectionalLight m_directionalLight2;
	PointLight m_pointLight;

	void clearScreen();

	QString getOpenGLVersion(QOPENGLFUNCTIONS_CLASSNAME &f);
	void setClearColor(QOPENGLFUNCTIONS_CLASSNAME &, const Vector3f &color);
	void enableTextures(QOPENGLFUNCTIONS_CLASSNAME &, bool isEnabled);
	void unbindTextures(QOPENGLFUNCTIONS_CLASSNAME &f);
};

#endif // RENDERINGENGINE_H
