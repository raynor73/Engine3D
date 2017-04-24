#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QList>
#include <engine/core/gamecomponent.h>
#include <engine/core/transform.h>
#include <engine/rendering/camera.h>
#include <engine/rendering/shader.h>

class GameObject : public QObject
{
	Q_OBJECT
public:
	explicit GameObject(QObject *parent = 0);

	virtual void onOpenGLResized(int width, int height);
	virtual void update(float dt);
	virtual void render(Camera &, Shader &);

	virtual void addChild(GameObject *);
	virtual void addComponent(GameComponent *);

	Transform &transform() { return m_transform; }

private:
	QList<GameObject *> m_children;
	QList<GameComponent *> m_components;
	Transform m_transform;
};

#endif // GAMEOBJECT_H
