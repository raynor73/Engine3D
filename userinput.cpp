#include <QApplication>
#include <QDebug>
#include <QPoint>
#include <QCursor>
#include "userinput.h"

UserInput::UserInput(QWidget &openGLSurface, QObject *parent) :
	QObject(parent),
	m_openGLSurface(openGLSurface)
{
	qApp->installEventFilter(this);
}

UserInput::~UserInput()
{
	qApp->removeEventFilter(this);
}

QPoint UserInput::pointerPosition()
{
	return m_openGLSurface.mapFromGlobal(QCursor::pos());
}

void UserInput::setPointerPosition(const QPoint &position)
{
	QCursor::setPos(m_openGLSurface.mapToGlobal(position));
}

void UserInput::setPointerVisible(bool isVisible)
{
	if (isVisible)
		m_openGLSurface.setCursor(Qt::ArrowCursor);
	else
		m_openGLSurface.setCursor(Qt::BlankCursor);
}

bool UserInput::eventFilter(QObject *object, QEvent *event)
{
	switch (event->type()) {
	case QEvent::MouseButtonDblClick:
	case QEvent::MouseButtonPress:
	case QEvent::MouseButtonRelease: {
		QMouseEvent mouseEvent = *static_cast<QMouseEvent *>(event);
		emit onMouseEvent(mouseEvent);
		return true;
	}

	case QEvent::KeyPress:
	case QEvent::KeyRelease: {
		QKeyEvent keyEvent = *static_cast<QKeyEvent *>(event);
		if (!keyEvent.isAutoRepeat()) {
			emit onKeyEvent(keyEvent);
		}
		return true;
	}

	default:
		return QObject::eventFilter(object, event);
	}
}
