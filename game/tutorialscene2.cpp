#include "tutorialscene2.h"
#include <QDebug>
#include <engine/rendering/renderutils.h>
#include <engine/components/directionallight.h>
#include <engine/components/pointlight.h>
#include <engine/components/spotlight.h>
#include <engine/components/meshrenderer.h>
#include <utils.h>

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
	m_planeObject->transform().translation().set(0, -1, 5);

	m_directionLightObject = new GameObject();
	m_directionalLight = new DirectionalLight(*f, m_coreEngine.renderingEngine(), Vector3f(0, 0, 1),
											  0.4, Vector3f(1, 1, 1));
	m_directionLightObject->addComponent(m_directionalLight);

	m_pointLightObject = new GameObject();
	m_pointLight = new PointLight(*f, m_coreEngine.renderingEngine(), Vector3f(0, 1, 0), 0.4, Attenuation(0, 0, 1));
	m_pointLightObject->addComponent(m_pointLight);

	m_spotLightObject = new GameObject();
	m_spotLight = new SpotLight(*f, m_coreEngine.renderingEngine(), Vector3f(0, 1, 1), 0.8, Attenuation(0, 0, 0.1),
								0.7);
	m_spotLightObject->addComponent(m_spotLight);
	m_spotLightObject->transform().setRotation(*Quaternion().initRotation(Vector3f(0, 1, 0), Utils::toRadians(-90)));

	m_spotLight->transform().translation().set(5, 0, 5);

	m_rootGameObject->addChild(m_planeObject);
	m_rootGameObject->addChild(m_directionLightObject);
	m_rootGameObject->addChild(m_pointLightObject);
	m_rootGameObject->addChild(m_spotLightObject);
}

void TutorialScene2::onOpenGLResized(int width, int height)
{
	m_cameraGameObject = new GameObject();
	m_camera = new Camera(Utils::toRadians(70), float(width) / float(height), 0.01, 1000);
	m_cameraGameObject->addComponent(m_camera);
	m_rootGameObject->addChild(m_cameraGameObject);

	m_controller->setDisplaySize(width, height);
	m_controller->connectToEvents();
}

void TutorialScene2::update(float dt)
{
	float sensitivity = 0.5;

	m_controller->updatePointer();

	float moveAmount = 10 * dt;

	Vector3f forward = m_camera->transform().rotation().calculateForward();
	if (m_controller->movementDiretion() == TutorialController::MovementDiretion::Forward)
		m_camera->transform().setTranslation(m_camera->transform().translation() + forward * moveAmount);
	if (m_controller->movementDiretion() == TutorialController::MovementDiretion::Backward)
		m_camera->transform().setTranslation(m_camera->transform().translation() - forward * moveAmount);

	if (m_controller->strafeDirection() == TutorialController::StrafeDirection::Left)
		m_camera->transform().setTranslation(m_camera->transform().translation() +
											 m_camera->transform().rotation().calculateLeft() * moveAmount);
	if (m_controller->strafeDirection() == TutorialController::StrafeDirection::Right)
		m_camera->transform().setTranslation(m_camera->transform().translation() +
											 m_camera->transform().rotation().calculateRight() * moveAmount);

	if (m_controller->isGrabPointerRequested())
		m_controller->grabPointer();

	if (m_controller->isReleasePointerRequested())
		m_controller->releasePointer();

	if (m_controller->isPointerGrabbed()) {
		QPoint delta = m_controller->pointerDelta();
		m_camera->transform().setRotation(m_camera->transform().rotation() *
				(*Quaternion().initRotation(m_camera->yAxis, -Utils::toRadians(delta.x() * sensitivity))).normalized());
		m_camera->transform().setRotation(m_camera->transform().rotation() *
				(*Quaternion().initRotation(m_camera->transform().rotation().calculateRight(),
											-Utils::toRadians(delta.y() * sensitivity))).normalized());
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
	if (m_cameraGameObject != NULL)
		delete m_cameraGameObject;
	if (m_camera != NULL)
		delete m_camera;

	delete m_controller;
	delete m_rootGameObject;

	if (m_directionLightObject != NULL)
		delete m_directionLightObject;
	if (m_directionalLight != NULL)
		delete m_directionalLight;

	if (m_pointLightObject != NULL)
		delete m_pointLightObject;
	if (m_pointLight != NULL)
		delete m_pointLight;

	if (m_spotLightObject != NULL)
		delete m_spotLightObject;
	if (m_spotLight != NULL)
		delete m_spotLight;
}
