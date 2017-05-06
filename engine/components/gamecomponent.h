#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H

#include <QObject>
#include <QPointer>

class RenderingEngine;
class Camera;
class Shader;
class Transform;
class GameObject;
class GameComponent : public QObject
{
	Q_OBJECT
public:
	explicit GameComponent(QObject *parent = 0);

	virtual void onOpenGLResized(int width, int height);
	virtual void update(float) {}
	virtual void render(Camera &, Shader &) {}

	virtual void addToRenderingEngine(RenderingEngine &) {}

	GameObject *parentGameObject() { return m_parentGameObject; }
	void setParentGameObject(GameObject *gameObject) { m_parentGameObject = gameObject; }
	Transform &transform();

protected:
	GameObject *m_parentGameObject;
};

#endif // GAMECOMPONENT_H
