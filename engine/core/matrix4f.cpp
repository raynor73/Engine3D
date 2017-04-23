#include <QApplication>
#include <cmath>
#include <utils.h>
#include "matrix4f.h"

Matrix4f::Matrix4f(QObject *parent) : QObject(parent)
{}

Matrix4f::Matrix4f(const Matrix4f &other) :
	QObject(other.parent())
{
	m__data = other.m__data;
}

Matrix4f::~Matrix4f()
{}

int Matrix4f::offset(int row, int column)
{
	return row * SIZE + column;
}

std::array<float, Matrix4f::DATA_SIZE> Matrix4f::getM() const
{
	return m__data;
}

void Matrix4f::setM(const std::array<float, DATA_SIZE> &data)
{
	m__data = data;
}

float  Matrix4f::get(int row, int column)
{
	return m__data[offset(row, column)];
}

void Matrix4f::set(int row, int column, float value)
{
	m__data[offset(row, column)] = value;
}

Matrix4f *Matrix4f::initIdentity()
{
	m__data.fill(0);
	for (int i = 0; i < SIZE; i++) {
		m__data[offset(i, i)] = 1;
	}

	return this;
}

Matrix4f *Matrix4f::initTranslation(float x, float y, float z)
{
	initIdentity();

	m__data[offset(0, 3)] = x;
	m__data[offset(1, 3)] = y;
	m__data[offset(2, 3)] = z;

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

	m__data[offset(0, 0)] = x;
	m__data[offset(1, 1)] = y;
	m__data[offset(2, 2)] = z;

	return this;
}

Matrix4f *Matrix4f::initPerspective(float fov, float aspectRatio, float zNear, float zFar)
{
	initIdentity();

	auto tanHalfFov = std::tan(fov / 2);
	auto zRange = zNear - zFar;

	m__data[offset(0, 0)] = 1.0 / (tanHalfFov * aspectRatio);
	m__data[offset(1, 1)] = 1.0 / tanHalfFov;
	m__data[offset(3, 3)] = 0;
	m__data[offset(3, 2)] = 1;
	m__data[offset(2, 2)] = (-zNear - zFar) / zRange;
	m__data[offset(2, 3)] = 2 * zFar * zNear / zRange;

	return this;
}

Matrix4f *Matrix4f::initRotation(const Vector3f &forward, const Vector3f &up)
{
	initIdentity();

	Vector3f f = forward;
	f.normalized();

	Vector3f r = up;
	r.normalized();
	r = r.cross(f);

	Vector3f u = f.cross(r);

	m__data[offset(0, 0)] = r.x;
	m__data[offset(0, 1)] = r.y;
	m__data[offset(0, 2)] = r.z;

	m__data[offset(1, 0)] = u.x;
	m__data[offset(1, 1)] = u.y;
	m__data[offset(1, 2)] = u.z;

	m__data[offset(2, 0)] = f.x;
	m__data[offset(2, 1)] = f.y;
	m__data[offset(2, 2)] = f.z;

	return this;
}

Matrix4f Matrix4f::operator *(const Matrix4f &other)
{
	Matrix4f m;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			m.set(i, j, m__data[offset(i, 0)] * other.m__data[offset(0, j)] +
					m__data[offset(i, 1)] * other.m__data[offset(1, j)] +
					m__data[offset(i, 2)] * other.m__data[offset(2, j)] +
					m__data[offset(i, 3)] * other.m__data[offset(3, j)]);
		}
	}

	return m;
}
