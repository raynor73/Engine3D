#include <QApplication>
#include <QDebug>
#include "userinput.h"
#include "engineconfig.h"

UserInput::UserInput(QObject *parent) : QObject(parent)
{
    qApp->installEventFilter(this);
}

UserInput::~UserInput()
{
    qApp->removeEventFilter(this);
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

    case QEvent::MouseMove: {
        QMouseEvent mouseEvent = *static_cast<QMouseEvent *>(event);
        m_pointerX = mouseEvent.x();
        m_pointerY = mouseEvent.y();

        int width = EngineConfig::DISPLAY_WIDTH;
        int height = EngineConfig::DISPLAY_HEIGHT;

        if (m_pointerX >= width)
            m_pointerX = width - 1;

        if (m_pointerY >= height)
            m_pointerY = height - 1;

        if (m_pointerX < 0)
            m_pointerX = 0;

        if (m_pointerY < 0)
            m_pointerY = 0;

        emit onMouseEvent(mouseEvent);
        return true;
    }

    case QEvent::KeyPress:
    case QEvent::KeyRelease: {
        QKeyEvent keyEvent = *static_cast<QKeyEvent *>(event);
        if (!keyEvent.isAutoRepeat()) {
            emit onKeyEvent(keyEvent);
            return true;
        }
    }

    default:
        return QObject::eventFilter(object, event);
    }
}
