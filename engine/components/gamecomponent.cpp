#include "gamecomponent.h"
#include <engine/core/gameobject.h>

GameComponent::GameComponent(QObject *parent) : QObject(parent) {}

void GameComponent::onOpenGLResized(int, int) {}
void GameComponent::update(float) {}

Transform &GameComponent::transform()
{
	return m_parentGameObject->transform();
}
