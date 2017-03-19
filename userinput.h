#ifndef USERINPUT_H
#define USERINPUT_H

#include <QObject>
#include <QWidget>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>

class UserInput : public QObject
{
    Q_OBJECT

public:
    explicit UserInput(QObject *parent = 0);
    ~UserInput();

    int pointerX() { return m_pointerX; }
    int pointerY() { return m_pointerY; }

signals:
    void onKeyEvent(QKeyEvent);
    void onMouseEvent(QMouseEvent);

protected:
    virtual bool eventFilter(QObject *, QEvent *);

private:
    int m_pointerX;
    int m_pointerY;
};

#endif // USERINPUT_H
