#include <QDebug>
#include "tutorialcontroller.h"

TutorialController::TutorialController(UserInput &userInput, QObject *parent) :
    QObject(parent),
    m_userInput(userInput),
    m_isReadingUserInput(false)
{}

void TutorialController::connectToEvents()
{
    connect(&m_userInput, &UserInput::onKeyEvent, this, &TutorialController::onKeyEvent);
    connect(&m_userInput, &UserInput::onMouseEvent, this, &TutorialController::onMouseEvent);
}

TutorialController::~TutorialController()
{
    if (m_isReadingUserInput)
        connectToEvents();
}

void TutorialController::startReadingUserInput()
{
    connectToEvents();
    m_isReadingUserInput = true;
}

void TutorialController::disconnectFromEvents()
{
    disconnect(&m_userInput, &UserInput::onKeyEvent, this, &TutorialController::onKeyEvent);
    disconnect(&m_userInput, &UserInput::onMouseEvent, this, &TutorialController::onMouseEvent);
}

void TutorialController::stopReadingUserInput()
{
    disconnectFromEvents();
    m_isReadingUserInput = false;
}

void TutorialController::onKeyEvent(QKeyEvent event)
{
    if (event.key() == Qt::Key_Up) {
        if (event.type() == QEvent::KeyPress)
            qDebug() << "'Up' key pressed";
        else
            qDebug() << "'Up' key released";
    }
}

void TutorialController::onMouseEvent(QMouseEvent event) {
    if (event.button() == Qt::RightButton) {
        if (event.type() == QEvent::MouseButtonPress)
            qDebug("Right mouse button pressed at %d; %d", m_userInput.pointerX(), m_userInput.pointerY());
        else
            qDebug() << "Right mouse button released";
    }
}
