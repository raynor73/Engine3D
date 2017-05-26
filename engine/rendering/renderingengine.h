#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include <engine/components/camera.h>
#include <engine/core/gameobject.h>
#include <engine/rendering/qopenglfunctions_selector.h>
#include <engine/rendering/resourcemanagement/mappedvalues.h>
#include <QList>
#include <QMap>

class ForwardAmbientShader;
class ForwardDirectionalShader;
class ForwardPointShader;
class ForwardSpotShader;
class BaseLight;
class RenderingEngine : public MappedValues
{
public:
	RenderingEngine();
	virtual ~RenderingEngine();

	void onOpenGLResized(GameObject &gameObject, int width, int height);
	void render(GameObject &gameObject);

	Camera &mainCamera() const { Q_ASSERT(m_mainCamera != NULL); return *m_mainCamera; }

	BaseLight *activeLight() { return m_activeLight; }
	GLuint vertexArrayName() const { return m_vertexArrayName; }

	void addLight(BaseLight *light) { m_lights += light; }
	void setCamera(Camera *camera) { m_mainCamera = camera; }

	int samplerSlot(const QString &name) const;

private:
	QOPENGLFUNCTIONS_CLASSNAME f;
	GLuint m_vertexArrayName;
	Camera *m_mainCamera;
	ForwardAmbientShader *m_forwardAmbientShader;
	QMap<QString, int> m_samplerMap;

	// More Permanent structures
	QList<BaseLight *> m_lights;
	BaseLight *m_activeLight;

	QString getOpenGLVersion(QOPENGLFUNCTIONS_CLASSNAME &f);
	void setClearColor(QOPENGLFUNCTIONS_CLASSNAME &, const Vector3f &color);
	void enableTextures(QOPENGLFUNCTIONS_CLASSNAME &, bool isEnabled);
	void unbindTextures(QOPENGLFUNCTIONS_CLASSNAME &f);
};

#endif // RENDERINGENGINE_H
