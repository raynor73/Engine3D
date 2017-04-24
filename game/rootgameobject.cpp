#include "rootgameobject.h"
#include <QDebug>

RootGameObject::RootGameObject(QObject *parent) :
	GameObject(parent),
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

void RootGameObject::render(Camera &camera, Shader &shader)
{
	GameObject::render(camera, shader);

	m_fpsCounter++;
}
