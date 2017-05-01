#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H

#include <QObject>
#include <engine/core/transform.h>
#include <engine/rendering/shader.h>
#include <engine/rendering/camera.h>

class RenderingEngine;
class GameComponent : public QObject
{
	Q_OBJECT
public:
	explicit GameComponent(QObject *parent = 0);

	virtual void onOpenGLResized(int width, int height);
	virtual void update(Transform &, float) {}
	virtual void render(Transform &, Camera &, Shader &) {}

	virtual void addToRenderingEngine() {}
};

#endif // GAMECOMPONENT_H
