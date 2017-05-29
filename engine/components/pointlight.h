#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <QObject>
#include <engine/components/baselight.h>
#include <engine/components/attenuation.h>
#include <engine/core/vector3f.h>
#include <engine/rendering/qopenglfunctions_selector.h>
#include <QSharedPointer>
#include <engine/rendering/shader.h>

class RenderingEngine;
class QOPENGLFUNCTIONS_CLASSNAME;
class PointLight : public BaseLight
{
	Q_OBJECT
public:
	PointLight(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine, const Vector3f &color, float intensity,
			   const Attenuation &attenuation, QSharedPointer<Shader> shader, QObject *parent = 0);

	Attenuation attenuation() const { return m_attenuation; }
	void setAttenuation(const Attenuation &attenuation) { m_attenuation = attenuation; }
	float range() { return m_range; }

protected:
	Attenuation m_attenuation;
	float m_range;

private:
	static const int COLOR_DEPTH = 256;
};

#endif // POINTLIGHT_H
