#ifndef COREENGINE_H
#define COREENGINE_H

#include <QObject>
#include <QString>
#include <game/scene.h>
#include <engine/rendering/mainwindow.h>
#include <engine/core/userinput.h>

class CoreEngine : public QObject
{
	Q_OBJECT
public:
	CoreEngine(int, int, float, const QString &, QObject *parent = 0);
	~CoreEngine();

	UserInput *userInput() { return m_mainWindow->userInput(); }
	Scene *scene() const { return m_scene; }
	float fps() { return m_mainWindow->openGLWidget()->fps(); }
	void setScene(Scene *);

public slots:
	void onOpenGLReady();
	void onOpenGLResized(int, int);
	void onRender();

private:
	MainWindow *m_mainWindow;
	Scene *m_scene;
	bool m_isOpenGLReady;
	bool m_isOpenGLSizeKnown;
	int m_openGLWidth;
	int m_openGLHeight;
};

#endif // COREENGINE_H
