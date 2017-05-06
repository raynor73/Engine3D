#include "gamecomponent.h"
#include <engine/core/gameobject.h>

GameComponent::GameComponent(QObject *parent) : QObject(parent) {}

void GameComponent::onOpenGLResized(int, int) {}

Transform &GameComponent::transform()
{
	return m_parentGameObject->transform();
}
