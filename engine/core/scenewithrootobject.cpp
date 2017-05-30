#include "scenewithrootobject.h"
#include <engine/core/gameobject.h>

SceneWithRootObject::SceneWithRootObject(QObject *parent) :
	SceneWithTimeMeasurement(parent),
	m_rootGameObject(NULL)
{}

void SceneWithRootObject::update(float dt)
{
	Q_ASSERT(m_rootGameObject != NULL);

	m_rootGameObject->updateAll(dt);
}
