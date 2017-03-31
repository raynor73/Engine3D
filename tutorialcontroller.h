#ifndef TUTORIALCONTROLLER_H
#define TUTORIALCONTROLLER_H

#include <QObject>
#include <QPoint>
#include "userinput.h"

class TutorialController : public QObject
{
	Q_OBJECT
public:
	struct MovementDiretion {
		enum Variants { Forward, Backward, Idle };
	};

	struct StrafeDirection {
		enum Variants { Left, Right, Idle };
	};

	struct PitchDirection {
		enum Variants { LookDown, LookUp, Idle };
	};

	struct YawDirection {
		enum Variants { TurnLeft, TurnRight, Idle };
	};

	explicit TutorialController(UserInput &userInput, QObject *parent = 0);
	~TutorialController();

	void startReadingUserInput();
	void stopReadingUserInput();

	MovementDiretion::Variants movementDiretion() { return m_movementDirection; }
	StrafeDirection::Variants strafeDirection() { return m_strafeDirection; }
	PitchDirection::Variants pitchDirection() { return m_pitchDirection; }
	YawDirection::Variants yawDirection() { return m_yawDirection; }
	QPoint pointerDelta() { return m_pointerDelta; }

public slots:
	void onKeyEvent(QKeyEvent);

private:
	UserInput &m_userInput;
	bool m_isReadingUserInput;
	MovementDiretion::Variants m_movementDirection;
	StrafeDirection::Variants m_strafeDirection;
	PitchDirection::Variants m_pitchDirection;
	YawDirection::Variants m_yawDirection;
	bool m_isPointerGrabbed;
	bool m_isPrevPointerPositionKnown;
	QPoint m_prevPointerPosition;
	QPoint m_pointerDelta;

	void connectToEvents();
	void disconnectFromEvents();
	void grabPointer();
	void releasePointer();
	void movePointerToCenter();
};

#endif // TUTORIALCONTROLLER_H
