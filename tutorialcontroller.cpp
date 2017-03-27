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
		disconnectFromEvents();
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
	if (event.type() == QEvent::KeyPress) {
		switch (event.key()) {
		case Qt::Key_W:
			m_movementDirection = Forward;
			break;

		case Qt::Key_S:
			m_movementDirection = Backward;
			break;

		case Qt::Key_A:
			m_strafeDirection = Left;
			break;

		case Qt::Key_D:
			m_strafeDirection = Right;
			break;

		case Qt::Key_Up:
			m_pitchDirection = LookDown;
			break;

		case Qt::Key_Down:
			m_pitchDirection = LookUp;
			break;

		case Qt::Key_Left:
			m_yawDirection = LookLeft;
			break;

		case Qt::Key_Right:
			m_yawDirection = LookRight;
			break;
		}
	} else {
		case Qt::Key_W:
			m_movementDirection = Forward;
			break;

		case Qt::Key_S:
			m_movementDirection = Backward;
			break;

		case Qt::Key_A:
			m_strafeDirection = Left;
			break;

		case Qt::Key_D:
			m_strafeDirection = Right;
			break;

		case Qt::Key_Up:
			m_pitchDirection = LookDown;
			break;

		case Qt::Key_Down:
			m_pitchDirection = LookUp;
			break;

		case Qt::Key_Left:
			m_yawDirection = LookLeft;
			break;

		case Qt::Key_Right:
			m_yawDirection = LookRight;
			break;
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
