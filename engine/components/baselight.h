#ifndef BASELIGHT_H
#define BASELIGHT_H

#include <QObject>
#include <engine/core/vector3f.h>
#include <engine/components/gamecomponent.h>
#include <engine/rendering/qopenglfunctions_selector.h>
#include <engine/rendering/shader.h>
#include <QSharedPointer>

class RenderingEngine;
class QOPENGLFUNCTIONS_CLASSNAME;
class BaseLight : public GameComponent
{
	Q_OBJECT

public:
	BaseLight(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngine, const Vector3f &color, float intensity,
			  QObject *parent = 0);

	Vector3f color() const { return m_color; }
	float intensity() const { return m_intensity; }
	void setColor(const Vector3f &color) { m_color = color; }
	void setIntensity(float intensity) { m_intensity = intensity; }
	QSharedPointer<Shader> shader() { return m_shader; }

	virtual void addToRenderingEngine(RenderingEngine &) override;

protected:
	QOPENGLFUNCTIONS_CLASSNAME &f;
	RenderingEngine &m_renderingEngine;
	Vector3f m_color;
	float m_intensity;
	QSharedPointer<Shader> m_shader;
};

#endif // BASELIGHT_H
