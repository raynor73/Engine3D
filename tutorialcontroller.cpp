#include "tutorialcontroller.h"

TutorialController::TutorialController(UserInput &userInput, QObject *parent) :
    QObject(parent),
    m_userInput(userInput),
    m_isReadingUserInput(false)
{}

void TutorialController::startReadUserInput()
{
    connect(m_userInput, &UserInput::onKeyEvent, this, &TutorialController::onKeyEvent);
    connect(m_userInput, &UserInput::onMouseEvent, this, &TutorialController::onMouseEvent);

    m_isReadingUserInput = true;
}

void TutorialController::stopReadUserInput()
{
    disconnect(m_userInput, &UserInput::onKeyEvent, this, &TutorialController::onKeyEvent);
    disconnect(m_userInput, &UserInput::onMouseEvent, this, &TutorialController::onMouseEvent);

    m_isReadingUserInput = false;
}

void TutorialController::onKeyEvent(QKeyEvent *)
{

}

void TutorialController::onMouseEvent(QMouseEvent *) {}

