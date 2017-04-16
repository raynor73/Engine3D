#ifndef DEFAULTSCENE_H
#define DEFAULTSCENE_H

#include <QObject>
#include <QOpenGLFunctions>
#include <engine/core/scene.h>

class DefaultScene : public Scene, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit DefaultScene(QObject *parent = 0);

    virtual void start();
    virtual void stop();
    virtual void render();
};

#endif // DEFAULTSCENE_H
