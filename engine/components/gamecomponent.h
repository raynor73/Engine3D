#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H

#include <QObject>
#include <QPointer>

class RenderingEngine;
class Camera;
class Shader;
class Transform;
class GameObject;
class CoreEngine;
class GameComponent : public QObject
{
	Q_OBJECT
public:
	explicit GameComponent(QObject *parent = 0);

	virtual void onOpenGLResized(int width, int height);
	virtual void update(float dt);
	virtual void render(Shader &, RenderingEngine&) {}

	virtual void addToEngine(CoreEngine &) {}

	GameObject *parentGameObject() { return m_parentGameObject; }
	void setParentGameObject(GameObject *gameObject) { m_parentGameObject = gameObject; }
	Transform &transform();

protected:
	GameObject *m_parentGameObject;
};

#endif // GAMECOMPONENT_H
