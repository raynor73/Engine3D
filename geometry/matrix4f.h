#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <QObject>

class Matrix4f : public QObject
{
	Q_OBJECT
public:
	static const int SIZE = 4;

	explicit Matrix4f(QObject *parent = 0);
	Matrix4f(const Matrix4f &);
	~Matrix4f();

	float (*getM())[SIZE];
	void setM(float (*)[SIZE]);
	float get(int, int);
	void set(int, int, float);
	Matrix4f *initIdentity();
	Matrix4f *initTranslation(float, float, float);
	Matrix4f *initRotation(float, float, float);
	Matrix4f *initScale(float, float, float);
	Matrix4f *initProjection(float, float, float, float, float);
	Matrix4f operator *(const Matrix4f &);

private:
	float m_data[SIZE][SIZE];
};

#endif // MATRIX4F_H
