#include "gameobject.h"

GameObject::GameObject(Camera *camera, float fov, float zNear, float zFar, QObject *parent) :
	QObject(parent)
{}

GameObject::~GameObject()
{}

void GameObject::onOpenGLResized(int width, int height)
{
	for (QList<GameComponent *>::Iterator i = m_components.begin(); i != m_components.end(); ++i)
		(*i)->onOpenGLResized(width, height);

	for (QList<GameObject *>::Iterator i = m_children.begin(); i != m_children.end(); ++i)
		(*i)->onOpenGLResized(width, height);
}

void GameObject::update(float dt)
{
	for (QList<GameComponent *>::Iterator i = m_components.begin(); i != m_components.end(); ++i)
		(*i)->update(m_transform, dt);

	for (QList<GameObject *>::Iterator i = m_children.begin(); i != m_children.end(); ++i)
		(*i)->update(dt);
}

void GameObject::render(Shader &shader)
{
	for (QList<GameComponent *>::Iterator i = m_components.begin(); i != m_components.end(); ++i)
		(*i)->render(m_transform, shader);

	for (QList<GameObject *>::Iterator i = m_children.begin(); i != m_children.end(); ++i)
		(*i)->render(shader);
}

void GameObject::addChild(GameObject *child)
{
	m_children += child;
}

void GameObject::addComponent(GameComponent *component)
{
	m_components += component;
}
