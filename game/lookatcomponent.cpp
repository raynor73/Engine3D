#include "lookatcomponent.h"
#include <engine/core/coreengine.h>

LookAtComponent::LookAtComponent(QObject *parent) :
	GameComponent(parent)
{}

void LookAtComponent::update(float dt)
{
	m_engine->renderingEngine().mainCamera()
}

void LookAtComponent::addToEngine(CoreEngine &engine)
{
	m_engine = &engine;
}
