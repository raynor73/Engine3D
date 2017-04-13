#ifndef COREENGINE_H
#define COREENGINE_H

#include <QObject>
#include <QString>
#include <game/scene.h>

class CoreEngine : public QObject
{
	Q_OBJECT
public:
	CoreEngine(int, int, float, const QString &, QObject *parent = 0);

	Scene *scene() const { return m_scene; }
	void setScene(Scene *scene) { m_scene = scene; }

private:
	Scene *m_scene;
};

#endif // COREENGINE_H
