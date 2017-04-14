#include "tutorialcontroller.h"
#include <QDebug>

TutorialController::TutorialController(UserInput &userInput, int displayWidth, int displayHeight, QObject *parent) :
	QObject(parent),
	m_userInput(userInput),
	m_isReadingUserInput(false),
	m_movementDirection(MovementDiretion::Idle),
	m_strafeDirection(StrafeDirection::Idle),
	m_pitchDirection(PitchDirection::Idle),
	m_yawDirection(YawDirection::Idle),
	m_isPointerGrabbed(false),
	m_isPrevPointerPositionKnown(false),
	m_isGrabPointerRequested(false),
	m_isReleasePointerRequested(false),
	m_isDisplaySizeKnown(false)
{}

void TutorialController::setDisplaySize(int displayWidht, int displayHeight)
{
	m_displayWidth = displayWidht;
	m_displayHeight = displayHeight;
	m_isDisplaySizeKnown = true;
}

void TutorialController::connectToEvents()
{
	connect(&m_userInput, &UserInput::onKeyEvent, this, &TutorialController::onKeyEvent);
	connect(&m_userInput, &UserInput::onMouseEvent, this, &TutorialController::onMouseEvent);
}

TutorialController::~TutorialController()
{
	if (m_isReadingUserInput)
		disconnectFromEvents();

	if (m_isPointerGrabbed)
		releasePointer();
}

void TutorialController::movePointerToCenter()
{
	m_userInput.setPointerPosition(QPoint(m_displayWidth / 2, m_displayHeight / 2));
}

void TutorialController::grabPointer()
{
	m_userInput.setPointerVisible(false);
	movePointerToCenter();

	m_isPointerGrabbed = true;
}

void TutorialController::releasePointer()
{
	m_userInput.setPointerVisible(true);

	m_isPointerGrabbed = false;
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

		case Qt::Key_Escape:
			m_isReleasePointerRequested = true;
			m_isGrabPointerRequested = false;
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

		case Qt::Key_Escape:
			m_isReleasePointerRequested = false;
			break;
		}
	}
}

void TutorialController::updatePointer()
{
	Q_ASSERT(m_isDisplaySizeKnown);

	if (m_isPointerGrabbed) {
		QPoint currentPointerPosition = m_userInput.pointerPosition();

		if (m_displayWidth / 2 != currentPointerPosition.x() || m_displayHeight / 2 != currentPointerPosition.y()) {
			m_prevPointerPosition = QPoint(m_displayWidth / 2, m_displayHeight / 2);
			m_pointerDelta = currentPointerPosition - m_prevPointerPosition;
		} else {
			m_pointerDelta = QPoint(0, 0);
		}

		movePointerToCenter();
	}
}

void TutorialController::onMouseEvent(QMouseEvent event) {
	if (event.button() == Qt::LeftButton && !m_isPointerGrabbed)
		m_isGrabPointerRequested = event.type() == QEvent::MouseButtonPress;
}
