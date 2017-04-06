#ifndef ATTENUATION_H
#define ATTENUATION_H

#include <QObject>

class Attenuation : public QObject
{
	Q_OBJECT
public:
	Attenuation(float, float, float, QObject *parent = 0);
	Attenuation(const Attenuation &);

	Attenuation &operator =(const Attenuation &);

	float constant() const { return m_constant; }
	float linear() const { return m_linear; }
	float exponent() const { return m_exponent; }
	void setConstant(float constant) { m_constant = constant; }
	void setLinear(float linear) { m_linear = linear; }
	void setExponent(float exponent) { m_exponent = exponent; }

private:
	float m_constant;
	float m_linear;
	float m_exponent;
};

#endif // ATTENUATION_H
