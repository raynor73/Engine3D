#ifndef SCENEWITHROOTOBJECT_H
#define SCENEWITHROOTOBJECT_H

#include <engine/core/scenewithtimemeasurement.h>
#include <engine/core/gameobject.h>

class SceneWithRootObject : public SceneWithTimeMeasurement
{
	Q_OBJECT
public:
	explicit SceneWithRootObject(QObject *parent = 0);

	GameObject *rootGameObject() { return m_rootGameObject; }

	virtual void makeOpenGLDependentSetup();
	virtual void onOpenGLResized(int width, int height);
	virtual void update(float dt);
	virtual void render();

protected:
	GameObject *m_rootGameObject;
};

#endif // SCENEWITHROOTOBJECT_H
