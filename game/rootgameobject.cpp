#include "rootgameobject.h"
#include <QDebug>

RootGameObject::RootGameObject(Camera *camera, float fov, float zNear, float zFar, QObject *parent) :
	GameObject(camera, fov, zNear, zFar, parent),
	m_fpsCounter(0)
{
	connect(&m_fpsTimer, &QTimer::timeout, [this]() {
		qDebug() << "FPS" << m_fpsCounter;
		m_fpsCounter = 0;
	});

	m_fpsTimer.start(1000);
}

RootGameObject::~RootGameObject()
{
	m_fpsTimer.stop();
}

void RootGameObject::render(Shader &shader)
{
	GameObject::render(shader);

	m_fpsCounter++;
}
