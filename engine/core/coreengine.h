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
	~CoreEngine();

	Scene *scene() const { return m_scene; }

public slots:
	void onOpenGLReady();

private:
	Scene *m_scene;
	bool m_isOpenGLReady;
};

#endif // COREENGINE_H
