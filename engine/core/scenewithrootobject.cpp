#include "scenewithrootobject.h"

SceneWithRootObject::SceneWithRootObject(QObject *parent) :
	SceneWithTimeMeasurement(parent),
	m_rootGameObject(NULL)
{}

void SceneWithRootObject::makeOpenGLDependentSetup()
{
	Q_ASSERT(m_rootGameObject != NULL);

	m_rootGameObject->makeOpenGLDependentSetup();
}

void SceneWithRootObject::onOpenGLResized(int width, int height)
{
	Q_ASSERT(m_rootGameObject != NULL);

	m_rootGameObject->onOpenGLResized(width, height);
}

void SceneWithRootObject::update(float dt)
{
	Q_ASSERT(m_rootGameObject != NULL);

	m_rootGameObject->update(dt);
}

void SceneWithRootObject::render()
{
	Q_ASSERT(m_rootGameObject != NULL);

	m_rootGameObject->render();
}
