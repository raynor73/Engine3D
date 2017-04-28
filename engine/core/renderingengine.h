#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include <QObject>
#include <engine/rendering/camera.h>
#include <engine/core/gameobject.h>
#include <engine/rendering/qopenglfunctions_selector.h>
#include <engine/components/directionallight.h>
#include <engine/components/pointlight.h>
#include <engine/rendering/spotlight.h>
#include <QList>

class ForwardAmbientShader;
class ForwardDirectionalShader;
class ForwardPointShader;
class ForwardSpotShader;
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
	DirectionalLight &directionalLight() { return *m_activeDirectionalLight; }
	PointLight &pointLight() { return *m_activePointLight; }
	SpotLight &spotLight() { return *m_activeSpotLight; }

	void addDirectionalLight(DirectionalLight *directionalLight) { m_directionalLights += directionalLight; }
	void addPointLight(PointLight *pointLight) { m_pointLights += pointLight; }

private:
	QOPENGLFUNCTIONS_CLASSNAME f;
	Camera *m_mainCamera;
	ForwardAmbientShader *m_forwardAmbientShader;
	ForwardDirectionalShader *m_forwardDirectionalShader;
	ForwardPointShader *m_forwardPointShader;
	ForwardSpotShader *m_forwarSpotShader;
	Vector3f m_ambientLight;
	DirectionalLight *m_activeDirectionalLight;
	PointLight *m_activePointLight;
	SpotLight *m_activeSpotLight;

	// Premanent structures
	QList<DirectionalLight *> m_directionalLights;
	QList<PointLight *> m_pointLights;

	void clearScreen();
	void clearLightList();

	QString getOpenGLVersion(QOPENGLFUNCTIONS_CLASSNAME &f);
	void setClearColor(QOPENGLFUNCTIONS_CLASSNAME &, const Vector3f &color);
	void enableTextures(QOPENGLFUNCTIONS_CLASSNAME &, bool isEnabled);
	void unbindTextures(QOPENGLFUNCTIONS_CLASSNAME &f);
};

#endif // RENDERINGENGINE_H
