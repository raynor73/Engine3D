#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include <QObject>
#include <engine/core/gameobject.h>

class RenderingEngine : public QObject
{
	Q_OBJECT
public:
	explicit RenderingEngine(QObject *parent = 0);

	void render(const GameObject &gameObject);
};

#endif // RENDERINGENGINE_H
