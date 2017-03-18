#ifndef SCENE_H
#define SCENE_H

#include <QObject>

class Scene : public QObject
{
    Q_OBJECT

public:
    explicit Scene(QObject *parent = 0);

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void render() = 0;
};

#endif // SCENE_H
