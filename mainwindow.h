#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "openglwidget.h"
#include "scene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    OpenGLWidget *m_openglWidget;
    Scene *m_scene;
};

#endif // MAINWINDOW_H
