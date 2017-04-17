#include "gamecomponent.h"

GameComponent::GameComponent(QObject *parent) : QObject(parent) {}

void GameComponent::onOpenGLResized(int, int) {}

void GameComponent::update(Transform &, float) {}

void GameComponent::render(Transform &, Shader &) {}
