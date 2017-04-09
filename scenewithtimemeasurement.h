#ifndef SCENEWITHTIMEMEASUREMENT_H
#define SCENEWITHTIMEMEASUREMENT_H

#include "scene.h"
#include <QElapsedTimer>

class SceneWithTimeMeasurement : public Scene
{
	Q_OBJECT

public:
	explicit SceneWithTimeMeasurement(QObject *parent = 0);

	virtual void update();

	virtual void update(float) = 0;

private:
	QElapsedTimer m_deltaTimer;
};

#endif // SCENEWITHTIMEMEASUREMENT_H
