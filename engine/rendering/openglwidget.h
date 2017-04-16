#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QElapsedTimer>

class OpenGLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	explicit OpenGLWidget(QWidget *, float);
	float fps() { return m_fps; }

signals:
	void openGLReady();
	void openGLResized(int, int);
	void render();

protected:
	void initializeGL();
	void resizeGL(int, int);
	void paintGL();

private:
	int m_fpsPeriod;
	float m_fps;
	QElapsedTimer m_renderTimer;
	QElapsedTimer m_fpsTimer;
};

#endif // OPENGLWIDGET_H
