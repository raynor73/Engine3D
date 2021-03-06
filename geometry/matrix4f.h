#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <QObject>

class Matrix4f : public QObject
{
    Q_OBJECT
public:
    explicit Matrix4f(QObject *parent = 0);
    Matrix4f(const Matrix4f &);
    ~Matrix4f();

    float **getM() { return m_data; }
    void setM(float **);
    float get(int, int);
    void set(int, int, float);
    Matrix4f *initIdentity();
    Matrix4f operator *(const Matrix4f &);

private:
    static const int SIZE = 4;

    float **m_data;
};

#endif // MATRIX4F_H
