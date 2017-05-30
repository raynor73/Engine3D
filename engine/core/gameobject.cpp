#include "gameobject.h"
#include <engine/rendering/renderingengine.h>
#include <engine/components/gamecomponent.h>
#include <engine/components/camera.h>

GameObject::GameObject(QObject *parent) :
	QObject(parent),
	m_coreEngine(NULL)
{}

void GameObject::onOpenGLResizedAll(int width, int height)
{
	onOpenGLResized(width, height);

	for (QList<GameObject *>::Iterator i = m_children.begin(); i != m_children.end(); ++i)
		(*i)->onOpenGLResizedAll(width, height);
}

void GameObject::updateAll(float dt)
{
	update(dt);

	for (QList<GameObject *>::Iterator i = m_children.begin(); i != m_children.end(); ++i)
		(*i)->updateAll(dt);
}

void GameObject::renderAll(Shader &shader, RenderingEngine &renderingEngine)
{
	render(shader, renderingEngine);

	for (QList<GameObject *>::Iterator i = m_children.begin(); i != m_children.end(); ++i)
		(*i)->renderAll(shader, renderingEngine);
}

void GameObject::onOpenGLResized(int width, int height)
{
	for (QList<GameComponent *>::Iterator i = m_components.begin(); i != m_components.end(); ++i)
		(*i)->onOpenGLResized(width, height);
}

void GameObject::update(float dt)
{
	for (QList<GameComponent *>::Iterator i = m_components.begin(); i != m_components.end(); ++i)
		(*i)->update(dt);
}

void GameObject::render(Shader &shader, RenderingEngine &renderingEngine)
{
	for (QList<GameComponent *>::Iterator i = m_components.begin(); i != m_components.end(); ++i)
		(*i)->render(shader, renderingEngine);
}

void GameObject::addChild(GameObject *child)
{
	m_children += child;
	child->setEngine(m_coreEngine);
	child->transform().setParentTransformation(&m_transform);
}

void GameObject::addComponent(GameComponent *component)
{
	m_components += component;
	component->setParentGameObject(this);
}

void GameObject::setEngine(CoreEngine *engine)
{
	if (m_coreEngine != engine) {
		m_coreEngine = engine;

		for (QList<GameComponent *>::Iterator i = m_components.begin(); i != m_components.end(); ++i)
			(*i)->addToEngine(*engine);

		for (QList<GameObject *>::Iterator i = m_children.begin(); i != m_children.end(); ++i)
			(*i)->setEngine(engine);
	}
}

QList<GameObject *> GameObject::descendantsAndSelf()
{
	QList<GameObject *> result;

	for (QList<GameObject *>::Iterator i = m_children.begin(); i != m_children.end(); ++i)
		result += (*i)->descendantsAndSelf();

	result += this;

	return result;
}
