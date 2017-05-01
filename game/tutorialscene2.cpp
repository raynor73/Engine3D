#include "tutorialscene2.h"
#include <QDebug>
#include <engine/rendering/renderutils.h>
#include <engine/components/directionallight.h>
#include <engine/components/pointlight.h>
#include <engine/components/meshrenderer.h>

TutorialScene2::TutorialScene2(CoreEngine &coreEngine, QObject *parent) :
	SceneWithRootObject(parent),
	f(NULL),
	m_coreEngine(coreEngine),
	m_mesh(NULL),
	m_texture(NULL),
	m_material(NULL),
	m_meshRenderer(NULL),
	m_planeObject(NULL)
{
	m_rootGameObject = new GameObject();
	m_controller = new TutorialController(m_coreEngine.userInput());

	connect(&m_fpsTimer, &QTimer::timeout, [this]() {
		qDebug() << "FPS" << m_coreEngine.fps();
	});
	m_fpsTimer.start(1000);
}

void TutorialScene2::makeOpenGLDependentSetup()
{
	f = new QOPENGLFUNCTIONS_CLASSNAME();
	f->initializeOpenGLFunctions();

	m_mesh = new Mesh(*f);
	QList<Vertex> vertices;
	QVector<unsigned int> indices;
	m_texture = new Texture(*f, "test.png");
	m_material = new Material(m_texture, Vector3f(1, 1, 1), 1, 8);

	float fieldDepth = 10;
	float fieldWidth = 10;

	vertices += Vertex(Vector3f(-fieldWidth, 0, -fieldDepth), Vector2f(0, 0));
	vertices += Vertex(Vector3f(-fieldWidth, 0, fieldDepth * 3), Vector2f(0, 1));
	vertices += Vertex(Vector3f(fieldWidth * 3, 0, -fieldDepth), Vector2f(1, 0));
	vertices += Vertex(Vector3f(fieldWidth * 3, 0, fieldDepth * 3), Vector2f(1, 1));

	indices += 0;
	indices += 1;
	indices += 2;
	indices += 2;
	indices += 1;
	indices += 3;

	m_mesh->setVertices(vertices, indices, true);

	m_meshRenderer = new MeshRenderer(m_mesh, m_material);
	m_planeObject = new GameObject();
	m_planeObject->addComponent(m_meshRenderer);
	m_planeObject->transform().setTranslation(0, -1, 5);

	m_directionLightObject = new GameObject();
	m_directionalLight = new DirectionalLight(*f, m_coreEngine.renderingEngine(), Vector3f(0, 0, 1),
											  0.4, Vector3f(1, 1, 1));
	m_directionLightObject->addComponent(m_directionalLight);

	m_pointLightObject = new GameObject();
	m_pointLight = new PointLight(*f, m_coreEngine.renderingEngine(), Vector3f(0, 1, 0), 0.4, Attenuation(0, 0, 1),
								  Vector3f(5, 0, 5), 100);
	m_pointLightObject->addComponent(m_pointLight);

	m_rootGameObject->addChild(m_planeObject);
	m_rootGameObject->addChild(m_directionLightObject);
	//m_rootGameObject->addChild(m_pointLightObject);
}

void TutorialScene2::onOpenGLResized(int width, int height)
{
	m_controller->setDisplaySize(width, height);
	m_controller->connectToEvents();
}

void TutorialScene2::update(float dt)
{
	float sensitivity = 0.5;

	m_controller->updatePointer();

	float moveAmount = 10 * dt;

	Camera &camera = m_coreEngine.renderingEngine().mainCamera();

	if (m_controller->movementDiretion() == TutorialController::MovementDiretion::Forward)
		camera.move(camera.forward(), moveAmount);
	if (m_controller->movementDiretion() == TutorialController::MovementDiretion::Backward)
		camera.move(camera.forward(), -moveAmount);

	if (m_controller->strafeDirection() == TutorialController::StrafeDirection::Left)
		camera.move(camera.calculateLeft(), moveAmount);
	if (m_controller->strafeDirection() == TutorialController::StrafeDirection::Right)
		camera.move(camera.calculateRight(), moveAmount);

	if (m_controller->isGrabPointerRequested())
		m_controller->grabPointer();

	if (m_controller->isReleasePointerRequested())
		m_controller->releasePointer();

	if (m_controller->isPointerGrabbed()) {
		QPoint delta = m_controller->pointerDelta();
		camera.rotateX(delta.y() * sensitivity);
		camera.rotateY(delta.x() * sensitivity);
	}

	m_rootGameObject->update(dt);
}

TutorialScene2::~TutorialScene2()
{
	m_fpsTimer.stop();
	m_controller->disconnectFromEvents();

	if (m_meshRenderer != NULL)
		delete m_meshRenderer;
	if (m_material != NULL)
		delete m_material;
	if (m_texture != NULL)
		delete m_texture;
	if (m_mesh != NULL)
		delete m_mesh;
	if (f != NULL)
		delete f;
	if (m_planeObject != NULL)
		delete m_planeObject;

	delete m_controller;
	delete m_rootGameObject;
	delete m_directionLightObject;
	delete m_directionalLight;
	delete m_pointLightObject;
	delete m_pointLight;
}
