#ifndef TUTORIALCONTROLLER_H
#define TUTORIALCONTROLLER_H

#include <QObject>
#include "userinput.h"

class TutorialController : public QObject
{
	Q_OBJECT
public:
	enum MovementDiretion {
		Forward, Backward, Idle
	};

	enum StrafeDirection {
		Left, Right, Idle
	};

	enum PitchDirection {
		LookDown, LookUp, Idle
	};

	enum YawDirection {
		LookLeft, LookRight, Idle
	};

	explicit TutorialController(UserInput &userInput, QObject *parent = 0);
	~TutorialController();

	void startReadingUserInput();
	void stopReadingUserInput();

	MovementDiretion movementDiretion() { return m_movementDirection; }
	StrafeDirection strafeDirection() { return m_strafeDirection; }
	PitchDirection pitchDirection() { return m_pitchDirection; }
	YawDirection yawDirection() { return m_yawDirection; }

public slots:
	void onKeyEvent(QKeyEvent);
	void onMouseEvent(QMouseEvent);

private:
	UserInput &m_userInput;
	bool m_isReadingUserInput;
	void connectToEvents();
	void disconnectFromEvents();

	MovementDiretion m_movementDirection;
	StrafeDirection m_strafeDirection;
	PitchDirection m_pitchDirection;
	YawDirection m_yawDirection;
};

#endif // TUTORIALCONTROLLER_H
