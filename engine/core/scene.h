#ifndef SCENE_H
#define SCENE_H

#include <QObject>

class CoreEngine;
class Scene : public QObject
{
	Q_OBJECT

public:
	explicit Scene(QObject *parent = 0);

	virtual void makeOpenGLDependentSetup() = 0;
	virtual void onOpenGLResized(int width, int height) = 0;
	virtual void update() = 0;
	virtual void setEngine(CoreEngine *) = 0;
};

#endif // SCENE_H
