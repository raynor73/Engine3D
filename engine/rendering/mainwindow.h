#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <engine/rendering/openglwidget.h>
#include <engine/core/userinput.h>
#include <engine/core/scene.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(int initialWidth, int initialHeight, float maxFps, QWidget *parent = 0);
	~MainWindow();

	OpenGLWidget &openGLWidget() { return *m_openglWidget; }
	UserInput &userInput() { return *m_userInput; }

private:
	Ui::MainWindow *ui;
	OpenGLWidget *m_openglWidget;
	UserInput *m_userInput;
};

#endif // MAINWINDOW_H
