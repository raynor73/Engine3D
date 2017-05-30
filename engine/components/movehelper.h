#ifndef MOVEHELPER_H
#define MOVEHELPER_H

#include "gamecomponent.h"
#include <engine/core/vector3f.h>

class MoveHelper : public GameComponent
{
	Q_OBJECT

public:
	explicit MoveHelper(QObject *parent = 0);

	void move(const Vector3f &direction, float amount);
};

#endif // MOVEHELPER_H
