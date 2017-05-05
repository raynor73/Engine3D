#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <QObject>
#include <array>
#include <engine/core/vector3f.h>

class Matrix4f : public QObject
{
	Q_OBJECT
public:
	static const int SIZE = 4;
	static const int DATA_SIZE = SIZE * SIZE;

	explicit Matrix4f(QObject *parent = 0);
	Matrix4f(const Matrix4f &);
	~Matrix4f();

	std::array<float, DATA_SIZE> getM() const;
	void setM(const std::array<float, DATA_SIZE> &);
	float get(int, int);
	void set(int, int, float);
	Matrix4f *initIdentity();
	Matrix4f *initTranslation(float, float, float);
	Matrix4f *initRotation(float, float, float);
	Matrix4f *initScale(float, float, float);
	Matrix4f *initPerspective(float fov, float aspectRatio, float zNear, float zFar);
	Matrix4f *initOrthographic(float left, float right, float bottom, float top, float near, float far);
	Matrix4f *initRotation(const Vector3f &, const Vector3f &);
	Matrix4f *initRotation(const Vector3f &forward, const Vector3f &up, const Vector3f &right);
	
	Matrix4f operator *(const Matrix4f &);
	Matrix4f &operator =(const Matrix4f &);

private:
	std::array<float, DATA_SIZE> m_data;

	inline int offset(int, int);
};

#endif // MATRIX4F_H
