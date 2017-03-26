#include <QApplication>
#include <cmath>
#include "utils.h"
#include "matrix4f.h"

Matrix4f::Matrix4f(QObject *parent) : QObject(parent)
{}

Matrix4f::Matrix4f(const Matrix4f &other) : Matrix4f(other.parent())
{
	std::copy(&other.m_data[0][0], &other.m_data[0][0] + SIZE * SIZE, &m_data[0][0]);
}

Matrix4f::~Matrix4f()
{}

float (*Matrix4f::getM())[SIZE]
{
	return m_data;
}

void Matrix4f::setM(float (*data)[SIZE])
{
	std::copy(&data[0][0], &data[0][0] + SIZE * SIZE, &m_data[0][0]);
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

Matrix4f *Matrix4f::initTranslation(float x, float y, float z)
{
	initIdentity();

	m_data[0][3] = x;
	m_data[1][3] = y;
	m_data[2][3] = z;

	return this;
}

Matrix4f *Matrix4f::initRotation(float x, float y, float z)
{
	initIdentity();

	Matrix4f rotationX, rotationY, rotationZ;

	float xRad = Utils::toRadians(x);
	float yRad = Utils::toRadians(y);
	float zRad = Utils::toRadians(z);

	rotationZ.initIdentity();
	rotationZ.set(0, 0, std::cos(zRad));
	rotationZ.set(0, 1, -std::sin(zRad));
	rotationZ.set(1, 0, std::sin(zRad));
	rotationZ.set(1, 1, std::cos(zRad));

	rotationX.initIdentity();
	rotationX.set(1, 1, std::cos(xRad));
	rotationX.set(1, 2, -std::sin(xRad));
	rotationX.set(2, 1, std::sin(xRad));
	rotationX.set(2, 2, std::cos(xRad));

	rotationY.initIdentity();
	rotationY.set(0, 0, std::cos(yRad));
	rotationY.set(0, 2, -std::sin(yRad));
	rotationY.set(2, 0, std::sin(yRad));
	rotationY.set(2, 2, std::cos(yRad));

	setM((rotationZ * rotationY * rotationX).getM());

	return this;
}

Matrix4f *Matrix4f::initScale(float x, float y, float z)
{
	initIdentity();

	m_data[0][0] = x;
	m_data[1][1] = y;
	m_data[2][2] = z;

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
