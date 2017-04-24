#ifndef ROOTGAMEOBJECT_H
#define ROOTGAMEOBJECT_H

#include <engine/core/gameobject.h>
#include <engine/rendering/shader.h>
#include <QTimer>

class RootGameObject : public GameObject
{
public:
	RootGameObject(QObject *parent = 0);
	virtual ~RootGameObject();

	virtual void render(Camera &, Shader &shader);

private:
	QTimer m_fpsTimer;
	int m_fpsCounter;
};

#endif // ROOTGAMEOBJECT_H
