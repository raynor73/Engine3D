#include <QDebug>
#include "tutorialcontroller.h"

TutorialController::TutorialController(UserInput &userInput, QObject *parent) :
	QObject(parent),
	m_userInput(userInput),
	m_isReadingUserInput(false),
	m_movementDirection(MovementDiretion::Idle),
	m_strafeDirection(StrafeDirection::Idle),
	m_pitchDirection(PitchDirection::Idle),
	m_yawDirection(YawDirection::Idle)
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
			m_movementDirection = MovementDiretion::Forward;
			break;

		case Qt::Key_S:
			m_movementDirection = MovementDiretion::Backward;
			break;

		case Qt::Key_A:
			m_strafeDirection = StrafeDirection::Left;
			break;

		case Qt::Key_D:
			m_strafeDirection = StrafeDirection::Right;
			break;

		case Qt::Key_Up:
			m_pitchDirection = PitchDirection::LookUp;
			break;

		case Qt::Key_Down:
			m_pitchDirection = PitchDirection::LookDown;
			break;

		case Qt::Key_Left:
			m_yawDirection = YawDirection::TurnLeft;
			break;

		case Qt::Key_Right:
			m_yawDirection = YawDirection::TurnRight;
			break;
		}
	} else {
		switch (event.key()) {
		case Qt::Key_W:
			m_movementDirection = MovementDiretion::Idle;
			break;

		case Qt::Key_S:
			m_movementDirection = MovementDiretion::Idle;
			break;

		case Qt::Key_A:
			m_strafeDirection = StrafeDirection::Idle;
			break;

		case Qt::Key_D:
			m_strafeDirection = StrafeDirection::Idle;
			break;

		case Qt::Key_Up:
			m_pitchDirection = PitchDirection::Idle;
			break;

		case Qt::Key_Down:
			m_pitchDirection = PitchDirection::Idle;
			break;

		case Qt::Key_Left:
			m_yawDirection = YawDirection::Idle;
			break;

		case Qt::Key_Right:
			m_yawDirection = YawDirection::Idle;
			break;
		}
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
