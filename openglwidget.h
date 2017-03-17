#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QElapsedTimer>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit OpenGLWidget(QWidget *, float);

protected:
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();

private:
    int m_fpsPeriod;
    float m_fps;
    QElapsedTimer m_renderTimer;
    QElapsedTimer m_fpsTimer;

    void doRender();
};

#endif // OPENGLWIDGET_H
