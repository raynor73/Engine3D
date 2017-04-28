#include "gameobject.h"
#include <engine/core/renderingengine.h>

GameObject::GameObject(QObject *parent) : QObject(parent) {}

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

void GameObject::render(Camera &camera, Shader &shader)
{
	for (QList<GameComponent *>::Iterator i = m_components.begin(); i != m_components.end(); ++i)
		(*i)->render(m_transform, camera, shader);

	for (QList<GameObject *>::Iterator i = m_children.begin(); i != m_children.end(); ++i)
		(*i)->render(camera, shader);
}

void GameObject::addChild(GameObject *child)
{
	m_children += child;
}

void GameObject::addComponent(GameComponent *component)
{
	m_components += component;
}

void GameObject::addToRenderingEngine(RenderingEngine &renderingEngine)
{
	for (QList<GameComponent *>::Iterator i = m_components.begin(); i != m_components.end(); ++i)
		(*i)->addToRenderingEngine(renderingEngine);

	for (QList<GameObject *>::Iterator i = m_children.begin(); i != m_children.end(); ++i)
		(*i)->addToRenderingEngine(renderingEngine);
}
