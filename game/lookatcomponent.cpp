#include "lookatcomponent.h"
#include <engine/core/coreengine.h>
#include <engine/core/quaternion.h>

LookAtComponent::LookAtComponent(QObject *parent) :
	GameComponent(parent),
	m_engine(NULL)
{}

void LookAtComponent::update(float dt)
{
	Camera &camera = m_engine->renderingEngine().mainCamera();
	Vector3f cameraTransformedTranslation = camera.transform().calculateTransformedTranslation();
	Quaternion newRotation = transform().calculateLookAtDirection(cameraTransformedTranslation, Vector3f(0, 1, 0));
	transform().setRotation(transform().rotation().nlerp(newRotation, dt * 5, true));
	//transform().setRotation(transform().rotation().slerp(newRotation, dt * 5, true));
}

void LookAtComponent::addToEngine(CoreEngine &engine)
{
	m_engine = &engine;
}
