#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H

#include <QObject>
#include <engine/core/transform.h>

class GameComponent : public QObject
{
	Q_OBJECT
public:
	explicit GameComponent(QObject *parent = 0);

	virtual void update(Transform &, float) {}
	virtual void render(Transform &) {}
};

#endif // GAMECOMPONENT_H
