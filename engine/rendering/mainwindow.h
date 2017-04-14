#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <engine/rendering/openglwidget.h>
#include <engine/core/userinput.h>
#include <game/scene.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(int, int, float, QWidget *parent = 0);
	~MainWindow();

	OpenGLWidget *openGLWidget() { return m_openglWidget; }
	UserInput *userInput() { return m_userInput; }

/*public slots:
	void onOpenGLReady();*/

private:
	Ui::MainWindow *ui;
	OpenGLWidget *m_openglWidget;
	//Scene *m_scene;
	UserInput *m_userInput;
};

#endif // MAINWINDOW_H
