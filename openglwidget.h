#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QElapsedTimer>
#include "scene.h"

class OpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit OpenGLWidget(QWidget *, float);
    void setScene(Scene *);

signals:
    void openGLReady();

protected:
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();

private:
    int m_fpsPeriod;
    float m_fps;
    QElapsedTimer m_renderTimer;
    QElapsedTimer m_fpsTimer;
    Scene *m_scene;
    bool m_isOpenGLReadySignalEmitted;
};

#endif // OPENGLWIDGET_H
