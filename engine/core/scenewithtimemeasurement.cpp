#include "scenewithtimemeasurement.h"

SceneWithTimeMeasurement::SceneWithTimeMeasurement(QObject *parent) : Scene(parent)
{}

void SceneWithTimeMeasurement::update()
{
	float dt = 0;
	if (m_deltaTimer.isValid())
		dt = m_deltaTimer.nsecsElapsed() / 1000000000.0f;

	m_deltaTimer.start();

	update(dt);
}
