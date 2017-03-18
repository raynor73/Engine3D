#ifndef DEFAULTSCENE_H
#define DEFAULTSCENE_H

#include <QObject>
#include <QOpenGLFunctions>
#include "scene.h"

class DefaultScene : public Scene
{
    Q_OBJECT

public:
    explicit DefaultScene(QObject *parent = 0);

    virtual void start();
    virtual void stop();
    virtual void render();

private:
     QOpenGLFunctions *m_openGLFunctions;
};

#endif // DEFAULTSCENE_H
