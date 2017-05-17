#include "gameobject.h"
#include <engine/rendering/renderingengine.h>
#include <engine/components/gamecomponent.h>
#include <engine/components/camera.h>

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
		(*i)->update(dt);

	for (QList<GameObject *>::Iterator i = m_children.begin(); i != m_children.end(); ++i)
		(*i)->update(dt);
}

void GameObject::render(Shader &shader, RenderingEngine &renderingEngine)
{
	for (QList<GameComponent *>::Iterator i = m_components.begin(); i != m_components.end(); ++i)
		(*i)->render(shader, renderingEngine);

	for (QList<GameObject *>::Iterator i = m_children.begin(); i != m_children.end(); ++i)
		(*i)->render(shader, renderingEngine);
}

void GameObject::addChild(GameObject *child)
{
	m_children += child;
	child->transform().setParentTransformation(&m_transform);
}

void GameObject::addComponent(GameComponent *component)
{
	m_components += component;
	component->setParentGameObject(this);
}

void GameObject::addToRenderingEngine(RenderingEngine &renderingEngine)
{
	for (QList<GameComponent *>::Iterator i = m_components.begin(); i != m_components.end(); ++i)
		(*i)->addToRenderingEngine(renderingEngine);

	for (QList<GameObject *>::Iterator i = m_children.begin(); i != m_children.end(); ++i)
		(*i)->addToRenderingEngine(renderingEngine);
}
