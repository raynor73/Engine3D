#ifndef TUTORIALCONTROLLER_H
#define TUTORIALCONTROLLER_H

#include <QObject>
#include "userinput.h"

class TutorialController : public QObject
{
    Q_OBJECT
public:
    explicit TutorialController(UserInput &userInput, QObject *parent = 0);
    ~TutorialController();

    void startReadingUserInput();
    void stopReadingUserInput();

public slots:
    void onKeyEvent(QKeyEvent);
    void onMouseEvent(QMouseEvent);

private:
    UserInput &m_userInput;
    bool m_isReadingUserInput;
    void connectToEvents();
    void disconnectFromEvents();
};

#endif // TUTORIALCONTROLLER_H
