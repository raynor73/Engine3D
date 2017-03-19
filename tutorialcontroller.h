#ifndef TUTORIALCONTROLLER_H
#define TUTORIALCONTROLLER_H

#include <QObject>
#include "userinput.h"

class TutorialController : public QObject
{
    Q_OBJECT
public:
    explicit TutorialController(UserInput &userInput, QObject *parent = 0);

    void startReadUserInput();
    void stopReadUserInput();

public slots:
    void onKeyEvent(QKeyEvent *);
    void onMouseEvent(QMouseEvent *);

private:
    UserInput &m_userInput;
    bool m_isReadingUserInput;
};

#endif // TUTORIALCONTROLLER_H
