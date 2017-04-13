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
	void setScene(Scene *);
	float fps() { return m_fps; }

signals:
	void openGLReady();
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
	bool m_isOpenGLReadySignalEmitted;
};

#endif // OPENGLWIDGET_H
