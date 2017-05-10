#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <QObject>
#include <engine/core/vector3f.h>
#include <engine/components/baselight.h>
#include <engine/rendering/qopenglfunctions_selector.h>

class QOPENGLFUNCTIONS_CLASSNAME;
class RenderingEngine;
class DirectionalLight : public BaseLight
{
	Q_OBJECT
public:
	DirectionalLight(QOPENGLFUNCTIONS_CLASSNAME &f, RenderingEngine &renderingEngien, const Vector3f &color,
					 float intensity, QObject *parent = 0);
	DirectionalLight(const DirectionalLight &);

	Vector3f direction();

	DirectionalLight &operator =(const DirectionalLight &);
};

#endif // DIRECTIONALLIGHT_H
