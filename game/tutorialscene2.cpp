#include "tutorialscene2.h"
#include <QDebug>
#include <engine/rendering/renderutils.h>
#include <engine/components/directionallight.h>
#include <engine/components/pointlight.h>
#include <engine/components/spotlight.h>
#include <engine/components/meshrenderer.h>
#include <engine/components/lightsfactory.h>
#include <engine/components/movehelper.h>
#include <utils.h>

TutorialScene2::TutorialScene2(CoreEngine &coreEngine, QObject *parent) :
	SceneWithRootObject(parent),
	f(NULL),
	m_coreEngine(coreEngine),
	m_mesh(NULL),
	m_mesh2(NULL),
	m_texture(NULL),
	m_material(NULL),
	m_meshRenderer(NULL),
	m_planeObject(NULL),
	m_testMesh1(NULL),
	m_testMesh2(NULL),
	m_meshRenderer1(NULL),
	m_meshRenderer2(NULL),
	m_monkeyMesh(NULL),
	m_monkeyGameObject(NULL),
	m_monkeyMeshRenderer(NULL),
	m_monkeyMesh2(NULL),
	m_monkeyGameObject2(NULL),
	m_monkeyMeshRenderer2(NULL),
	m_cameraGameObject(NULL),
	m_camera(NULL),
	m_lookAtComponent(NULL)
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
	m_texture = new Texture("brick.jpg");
	m_material = new Material();
	m_material->addTexture("diffuse", m_texture);
	m_material->addFloat("specularIntensity", 1);
	m_material->addFloat("specularPower", 8);

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

	QList<Vertex> vertices2;
	QVector<unsigned int> indices2;
	vertices2 += Vertex(Vector3f(-fieldWidth / 10, 0, -fieldDepth / 10), Vector2f(0, 0));
	vertices2 += Vertex(Vector3f(-fieldWidth / 10, 0, fieldDepth / 10 * 3), Vector2f(0, 1));
	vertices2 += Vertex(Vector3f(fieldWidth / 10 * 3, 0, -fieldDepth / 10), Vector2f(1, 0));
	vertices2 += Vertex(Vector3f(fieldWidth / 10 * 3, 0, fieldDepth / 10 * 3), Vector2f(1, 1));

	indices2 += 0;
	indices2 += 1;
	indices2 += 2;
	indices2 += 2;
	indices2 += 1;
	indices2 += 3;

	m_mesh2 = new Mesh(*f);
	m_mesh2->setVertices(vertices2, indices2, true);

	m_meshRenderer = new MeshRenderer(m_mesh, m_material);
	m_planeObject = new GameObject();
	m_planeObject->addComponent(m_meshRenderer);
	m_planeObject->transform().translation().set(0, -1, 5);

	m_directionLightObject = new GameObject();
	m_directionalLight = LightsFactory::createDirectionalLight(*f, m_coreEngine.renderingEngine(), Vector3f(0, 0, 1),
															   0.4);//new DirectionalLight(*f, m_coreEngine.renderingEngine(), Vector3f(0, 0, 1), 0.4);
	m_directionLightObject->transform().setRotation(Quaternion(Vector3f(1, 0, 0), Utils::toRadians(-45)));
	m_directionLightObject->addComponent(m_directionalLight.data());

	m_pointLightObject = new GameObject();
	m_pointLight = LightsFactory::createPointLight(*f, m_coreEngine.renderingEngine(), Vector3f(0, 1, 0), 0.4,
												   Attenuation(0, 0, 1));//new PointLight(*f, m_coreEngine.renderingEngine(), Vector3f(0, 1, 0), 0.4, Attenuation(0, 0, 1));
	m_pointLightObject->addComponent(m_pointLight.data());

	m_spotLightObject = new GameObject();
	m_spotLight = LightsFactory::createSpotLight(*f, m_coreEngine.renderingEngine(), Vector3f(0, 1, 1), 0.8,
												 Attenuation(0, 0, 0.1), 0.7);//new SpotLight(*f, m_coreEngine.renderingEngine(), Vector3f(0, 1, 1), 0.8, Attenuation(0, 0, 0.1), 0.7);
	m_spotLightObject->addComponent(m_spotLight.data());
	m_spotLightObject->transform().setRotation(Quaternion(Vector3f(0, 1, 0), Utils::toRadians(90)));

	m_spotLight->transform().translation().set(5, 0, 5);

	m_rootGameObject->addChild(m_planeObject);
	m_rootGameObject->addChild(m_directionLightObject);
	m_rootGameObject->addChild(m_pointLightObject);
	m_rootGameObject->addChild(m_spotLightObject);

	m_testMesh1 = new GameObject();
	m_testMesh2 = new GameObject();
	m_meshRenderer1 = new MeshRenderer(m_mesh2, m_material);
	m_meshRenderer2 = new MeshRenderer(m_mesh2, m_material);
	m_testMesh1->addComponent(m_meshRenderer1);
	m_testMesh2->addComponent(m_meshRenderer2);

	m_testMesh1->transform().translation().set(0, 2, 0);
	m_testMesh1->transform().setRotation(Quaternion(Vector3f(0, 1, 0), 0.4));

	m_testMesh2->transform().translation().set(0, 0, 5);

	m_testMesh1->addChild(m_testMesh2);

	m_rootGameObject->addChild(m_testMesh1);

	m_monkeyMesh = new Mesh(*f, "monkey2.obj");
	m_monkeyGameObject = new GameObject();
	m_monkeyMeshRenderer = new MeshRenderer(m_monkeyMesh, m_material);
	m_monkeyGameObject->addComponent(m_monkeyMeshRenderer);
	m_monkeyGameObject->transform().translation().set(5, 5, 5);
	m_monkeyGameObject->transform().setRotation(Quaternion(Vector3f(0, 1, 0), Utils::toRadians(-70)));

	//TODO Set engine to component in case when it added after parent object added to hierarchy
	m_lookAtComponent = new LookAtComponent();
	m_monkeyGameObject->addComponent(m_lookAtComponent);

	m_rootGameObject->addChild(m_monkeyGameObject);

	m_texture2 = new Texture("test.png");
	m_material2 = new Material();
	m_material2->addTexture("diffuse", m_texture2);
	m_material2->addFloat("specularIntensity", 1);
	m_material2->addFloat("specularPower", 8);
	m_monkeyMesh2 = new Mesh(*f, "monkey2.obj");
	m_monkeyGameObject2 = new GameObject();
	m_monkeyMeshRenderer2 = new MeshRenderer(m_monkeyMesh2, m_material2);
	m_monkeyGameObject2->addComponent(m_monkeyMeshRenderer2);
	m_rootGameObject->addChild(m_monkeyGameObject2);
}

void TutorialScene2::onOpenGLResized(int width, int height)
{
	if (m_cameraGameObject == NULL) {
		m_cameraGameObject = new GameObject();
		//TODO Make camera update aspect ratio every time opengl resized
		m_camera = new Camera(Utils::toRadians(70), float(width) / float(height), 0.01, 1000);
		m_cameraGameObject->addComponent(m_camera);
		//m_rootGameObject->addChild(m_cameraGameObject);
		m_testMesh2->addChild(m_cameraGameObject);
	}

	m_controller->setDisplaySize(width, height);
	//TODO Don't connect to events several times
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

		m_camera->transform().rotate(m_camera->yAxis, Utils::toRadians(delta.x() * sensitivity));
		m_camera->transform().rotate(m_camera->transform().rotation().calculateRight(),
									 Utils::toRadians(delta.y() * sensitivity));
	}

	m_rootGameObject->updateAll(dt);
}

void TutorialScene2::setEngine(CoreEngine *coreEngine)
{
	m_rootGameObject->setEngine(coreEngine);
}

TutorialScene2::~TutorialScene2()
{
	m_fpsTimer.stop();
	m_controller->disconnectFromEvents();

	if (m_lookAtComponent != NULL)
		delete m_lookAtComponent;

	if (m_testMesh1 != NULL)
		delete m_testMesh1;
	if (m_testMesh2 != NULL)
		delete m_testMesh2;
	if (m_meshRenderer1 != NULL)
		delete m_meshRenderer1;
	if (m_meshRenderer2 != NULL)
		delete m_meshRenderer2;

	if (m_monkeyGameObject != NULL)
		delete m_monkeyGameObject;
	if (m_monkeyMeshRenderer != NULL)
		delete m_monkeyMeshRenderer;
	if (m_monkeyMesh != NULL)
		delete m_monkeyMesh;

	if (m_monkeyGameObject2 != NULL)
		delete m_monkeyGameObject2;
	if (m_monkeyMeshRenderer2 != NULL)
		delete m_monkeyMeshRenderer2;
	if (m_monkeyMesh2 != NULL)
		delete m_monkeyMesh2;
	if (m_material2 != NULL)
		delete m_material2;
	if (m_texture2 != NULL)
		delete m_texture2;

	if (m_meshRenderer != NULL)
		delete m_meshRenderer;
	if (m_material != NULL)
		delete m_material;
	if (m_texture != NULL)
		delete m_texture;
	if (m_mesh != NULL)
		delete m_mesh;
	if (m_mesh2 != NULL)
		delete m_mesh2;
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

	if (m_pointLightObject != NULL)
		delete m_pointLightObject;

	if (m_spotLightObject != NULL)
		delete m_spotLightObject;
}
