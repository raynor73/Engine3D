#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "openglwidget.h"
#include "userinput.h"
#include "scene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(int, int, float, QWidget *parent = 0);
	~MainWindow();

public slots:
	void onOpenGLReady();

private:
	Ui::MainWindow *ui;
	OpenGLWidget *m_openglWidget;
	Scene *m_scene;
	UserInput *m_userInput;
};

#endif // MAINWINDOW_H
