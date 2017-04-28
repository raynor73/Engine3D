#include "gamecomponent.h"

GameComponent::GameComponent(QObject *parent) : QObject(parent) {}

void GameComponent::onOpenGLResized(int, int) {}
