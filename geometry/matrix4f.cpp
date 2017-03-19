#include <QApplication>
#include "matrix4f.h"

Matrix4f::Matrix4f(QObject *parent) : QObject(parent)
{
    m_data = new float*[SIZE];
    for (int i = 0; i < SIZE; i++)
       m_data[i] = new float[SIZE];
}

Matrix4f::Matrix4f(const Matrix4f &other) : Matrix4f(other.parent())
{
    for (int i = 0; i < SIZE; i++)
        std::copy(&m_data[i][0], &m_data[i][SIZE - 1], &other.m_data[i][0]);
}

Matrix4f::~Matrix4f()
{
    for (int i = 0; i < SIZE; i++)
       delete m_data[i];

    delete m_data;
}

void Matrix4f::setM(float **data)
{
    m_data = data;
}

float  Matrix4f::get(int row, int column)
{
    return m_data[row][column];
}

void Matrix4f::set(int row, int column, float value)
{
    m_data[row][column] = value;
}

Matrix4f *Matrix4f::initIdentity()
{
    for (int i = 0; i < SIZE; i++) {
        std::fill_n(&m_data[i][0], SIZE, 0);
        m_data[i][i] = 1;
    }

    return this;
}

Matrix4f Matrix4f::operator *(const Matrix4f &other)
{
    Matrix4f m;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            m.set(i, j, m_data[i][0] * other.m_data[0][j] +
                        m_data[i][1] * other.m_data[1][j] +
                        m_data[i][2] * other.m_data[2][j] +
                        m_data[i][3] * other.m_data[3][j]);
        }
    }

    return m;
}
