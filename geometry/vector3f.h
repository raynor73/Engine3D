#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <QObject>

class Vector3f : public QObject
{
    Q_OBJECT
public:
    float x;
    float y;
    float z;

    explicit Vector3f(float, float, float, QObject *parent = 0);
    Vector3f(const Vector3f &);

    float length();
};

#endif // VECTOR3F_H
