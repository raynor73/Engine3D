#ifndef SCENEWITHROOTOBJECT_H
#define SCENEWITHROOTOBJECT_H

#include <engine/core/scenewithtimemeasurement.h>

class GameObject;
class SceneWithRootObject : public SceneWithTimeMeasurement
{
	Q_OBJECT
public:
	explicit SceneWithRootObject(QObject *parent = 0);

	GameObject &rootGameObject() { return *m_rootGameObject; }

	using SceneWithTimeMeasurement::update;
	virtual void update(float dt);

protected:
	GameObject *m_rootGameObject;
};

#endif // SCENEWITHROOTOBJECT_H
