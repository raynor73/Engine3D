#ifndef TUTORIALSCENE2_H
#define TUTORIALSCENE2_H

#include <engine/core/scenewithrootobject.h>
#include <engine/core/userinput.h>
#include <engine/core/gameobject.h>
#include <engine/rendering/mesh.h>
#include <engine/rendering/material.h>
#include <engine/rendering/texture.h>
#include <engine/rendering/qopenglfunctions_selector.h>
#include <game/tutorialcontroller.h>
#include <engine/core/coreengine.h>
#include <QTimer>

class DirectionalLight;
class PointLight;
class MeshRenderer;
class TutorialScene2 : public SceneWithRootObject
{
	Q_OBJECT

public:
	TutorialScene2(CoreEngine &, QObject *parent = 0);
	virtual ~TutorialScene2();

	virtual void update(float);
	virtual void onOpenGLResized(int width, int height);
	virtual void makeOpenGLDependentSetup();

private:
	QOPENGLFUNCTIONS_CLASSNAME *f;
	CoreEngine &m_coreEngine;
	Mesh *m_mesh;
	Texture *m_texture;
	Material *m_material;
	MeshRenderer *m_meshRenderer;
	TutorialController *m_controller;
	GameObject *m_planeObject;
	QTimer m_fpsTimer;
	GameObject *m_directionLightObject;
	DirectionalLight *m_directionalLight;
	GameObject *m_pointLightObject;
	PointLight *m_pointLight;
};

#endif // TUTORIALSCENE2_H
