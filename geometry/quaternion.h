#ifndef QUATERNION_H
#define QUATERNION_H

#include <QObject>
#include "vector3f.h"

class Quaternion : public QObject
{
    Q_OBJECT
public:
    float x;
    float y;
    float z;
    float w;

    explicit Quaternion(float, float, float, float, QObject *parent = 0);
    Quaternion(const Quaternion &);

    float length();
    Quaternion *normalize();
    Quaternion conjugate();
    Quaternion operator *(const Quaternion &);
    Quaternion operator *(const Vector3f &);
};

#endif // QUATERNION_H
