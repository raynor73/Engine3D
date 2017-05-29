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
#include <QSharedPointer>
#include <engine/components/directionallight.h>
#include <engine/components/pointlight.h>
#include <engine/components/spotlight.h>

class DirectionalLight;
class PointLight;
class MeshRenderer;
class SpotLight;
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
	Mesh *m_mesh2;
	Texture *m_texture;
	Material *m_material;
	MeshRenderer *m_meshRenderer;
	TutorialController *m_controller;
	GameObject *m_planeObject;
	QTimer m_fpsTimer;

	GameObject *m_testMesh1;
	GameObject *m_testMesh2;
	MeshRenderer *m_meshRenderer1;
	MeshRenderer *m_meshRenderer2;

	Mesh *m_monkeyMesh;
	GameObject *m_monkeyGameObject;
	MeshRenderer *m_monkeyMeshRenderer;
	Mesh *m_monkeyMesh2;
	GameObject *m_monkeyGameObject2;
	Texture *m_texture2;
	Material *m_material2;
	MeshRenderer *m_monkeyMeshRenderer2;

	GameObject *m_directionLightObject;
	QSharedPointer<DirectionalLight> m_directionalLight;

	GameObject *m_pointLightObject;
	QSharedPointer<PointLight> m_pointLight;

	GameObject *m_spotLightObject;
	QSharedPointer<SpotLight> m_spotLight;

	GameObject *m_cameraGameObject;
	Camera *m_camera;
};

#endif // TUTORIALSCENE2_H
