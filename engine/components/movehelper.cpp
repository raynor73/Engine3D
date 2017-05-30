#include "movehelper.h"
#include <engine/core/transform.h>

MoveHelper::MoveHelper(QObject *parent) : GameComponent(parent) {}

void MoveHelper::move(const Vector3f &direction, float amount)
{
	transform().setTranslation(transform().translation() + direction * amount);
}
