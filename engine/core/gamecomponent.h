#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H

#include <QObject>
#include <engine/core/transform.h>

class GameComponent : public QObject
{
	Q_OBJECT
public:
	explicit GameComponent(QObject *parent = 0);

	virtual void onOpenGLResized(int width, int height);
	virtual void update(Transform &transform, float dt);
	virtual void render(Transform &transform);
};

#endif // GAMECOMPONENT_H
