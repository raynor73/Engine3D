#ifndef COREENGINE_H
#define COREENGINE_H

#include <QObject>
#include <QString>
#include <QPointer>
#include <engine/core/scenewithrootobject.h>
#include <engine/rendering/mainwindow.h>
#include <engine/core/userinput.h>
#include <engine/core/renderingengine.h>

class CoreEngine : public QObject
{
	Q_OBJECT
public:
	CoreEngine(int width, int height, float maxFps, const QString &title, QObject *parent = 0);
	~CoreEngine();

	UserInput &userInput() { return m_mainWindow->userInput(); }
	RenderingEngine &renderingEngine() { return *m_renderingEngine; }
	SceneWithRootObject *scene() const { return m_scene; }
	float fps() { return m_mainWindow->openGLWidget().fps(); }
	void setScene(SceneWithRootObject *);

public slots:
	void onOpenGLReady();
	void onOpenGLResized(int width, int height);
	void onRender();

private:
	RenderingEngine *m_renderingEngine;
	MainWindow *m_mainWindow;
	QPointer<SceneWithRootObject> m_scene;
	bool m_isOpenGLReady;
	bool m_isOpenGLSizeKnown;
	int m_openGLWidth;
	int m_openGLHeight;
};

#endif // COREENGINE_H
