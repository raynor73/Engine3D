#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include <QObject>
#include <engine/components/camera.h>
#include <engine/core/gameobject.h>
#include <engine/rendering/qopenglfunctions_selector.h>
#include <QList>

class ForwardAmbientShader;
class ForwardDirectionalShader;
class ForwardPointShader;
class ForwardSpotShader;
class BaseLight;
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
	BaseLight *activeLight() { return m_activeLight; }
	GLuint vertexArrayName() const { return m_vertexArrayName; }

	void addLight(BaseLight *light) { m_lights += light; }
	void setCamera(Camera *camera) { m_mainCamera = camera; }

private:
	QOPENGLFUNCTIONS_CLASSNAME f;
	GLuint m_vertexArrayName;
	Camera *m_mainCamera;
	ForwardAmbientShader *m_forwardAmbientShader;
	Vector3f m_ambientLight;

	// More Permanent structures
	QList<BaseLight *> m_lights;
	BaseLight *m_activeLight;

	void clearScreen();

	QString getOpenGLVersion(QOPENGLFUNCTIONS_CLASSNAME &f);
	void setClearColor(QOPENGLFUNCTIONS_CLASSNAME &, const Vector3f &color);
	void enableTextures(QOPENGLFUNCTIONS_CLASSNAME &, bool isEnabled);
	void unbindTextures(QOPENGLFUNCTIONS_CLASSNAME &f);
};

#endif // RENDERINGENGINE_H
