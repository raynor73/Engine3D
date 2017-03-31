#ifndef USERINPUT_H
#define USERINPUT_H

#include <QObject>
#include <QPoint>
#include <QWidget>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>

class UserInput : public QObject
{
	Q_OBJECT

public:
	explicit UserInput(QWidget &, QObject *parent = 0);
	~UserInput();

	QPoint pointerPosition();
	void setPointerPosition(const QPoint &);
	void setPointerVisible(bool);

signals:
	void onKeyEvent(QKeyEvent);

protected:
	virtual bool eventFilter(QObject *, QEvent *);

private:
	QWidget &m_openGLSurface;
};

#endif // USERINPUT_H
