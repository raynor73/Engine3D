#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QList>
#include <engine/core/transform.h>
#include <engine/rendering/shader.h>

class RenderingEngine;
class GameComponent;
class Camera;
class CoreEngine;
class GameObject : public QObject
{
	Q_OBJECT
public:
	explicit GameObject(QObject *parent = 0);

	virtual void onOpenGLResizedAll(int width, int height);
	virtual void updateAll(float dt);
	virtual void renderAll(Shader &, RenderingEngine &);

	void onOpenGLResized(int width, int height);
	void update(float dt);
	void render(Shader &, RenderingEngine &);

	virtual void addChild(GameObject *);
	virtual void addComponent(GameComponent *);

	Transform &transform() { return m_transform; }

	void setEngine(CoreEngine *coreEngine);

	QList<GameObject *> descendantsAndSelf();

private:
	CoreEngine *m_coreEngine;
	QList<GameObject *> m_children;
	QList<GameComponent *> m_components;
	Transform m_transform;
};

#endif // GAMEOBJECT_H
