#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include <QObject>
#include <engine/rendering/camera.h>
#include <engine/core/gameobject.h>
#include <engine/rendering/qopenglfunctions_selector.h>
#include <engine/rendering/directionallight.h>

class ForwardAmbientShader;
class ForwardDirectionalShader;
class RenderingEngine : public QObject
{
	Q_OBJECT
public:
	explicit RenderingEngine(QObject *parent = 0);
	virtual ~RenderingEngine();

	void onOpenGLResized(GameObject &gameObject, int width, int height);
	void render(GameObject &gameObject);
	Camera &mainCamera() const { Q_ASSERT(m_mainCamera != NULL); return *m_mainCamera; }
	Vector3f ambientLight() const { return m_ambientLight; }
	DirectionalLight directionalLight() const { return m_directionalLight; }

private:
	QOPENGLFUNCTIONS_CLASSNAME f;
	Camera *m_mainCamera;
	ForwardAmbientShader *m_forwardAmbientShader;
	ForwardDirectionalShader *m_forwardDirectionalShader;
	Vector3f m_ambientLight;
	DirectionalLight m_directionalLight;
	DirectionalLight m_directionalLight2;

	void clearScreen();

	QString getOpenGLVersion(QOPENGLFUNCTIONS_CLASSNAME &f);
	void setClearColor(QOPENGLFUNCTIONS_CLASSNAME &, const Vector3f &color);
	void enableTextures(QOPENGLFUNCTIONS_CLASSNAME &, bool isEnabled);
	void unbindTextures(QOPENGLFUNCTIONS_CLASSNAME &f);
};

#endif // RENDERINGENGINE_H
