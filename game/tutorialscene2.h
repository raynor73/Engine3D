#ifndef TUTORIALSCENE2_H
#define TUTORIALSCENE2_H

#include <engine/core/scenewithrootobject.h>
#include <engine/rendering/camera.h>
#include <engine/core/userinput.h>
#include <engine/core/gameobject.h>
#include <engine/rendering/mesh.h>
#include <engine/rendering/material.h>
#include <engine/rendering/texture.h>
#include <engine/rendering/qopenglfunctions_selector.h>
#include <game/meshrenderer.h>
#include <game/tutorialcontroller.h>
#include <QTimer>

class TutorialScene2 : public SceneWithRootObject
{
	Q_OBJECT

public:
	TutorialScene2(UserInput &, QObject *parent = 0);
	virtual ~TutorialScene2();

	virtual void update(float);
	virtual void makeOpenGLDependentSetup();

private:
	QOPENGLFUNCTIONS_CLASSNAME *m_openGLFunctions;
	Mesh *m_mesh;
	Texture *m_texture;
	Material *m_material;
	MeshRenderer *m_meshRenderer;
	TutorialController *m_controller;
	GameObject *m_planeObject;
};

#endif // TUTORIALSCENE2_H
