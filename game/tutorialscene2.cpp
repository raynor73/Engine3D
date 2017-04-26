#include "tutorialscene2.h"
#include <QDebug>
#include <engine/rendering/renderutils.h>

TutorialScene2::TutorialScene2(CoreEngine &coreEngine, QObject *parent) :
	SceneWithRootObject(parent),
	m_openGLFunctions(NULL),
	m_coreEngine(coreEngine),
	m_mesh(NULL),
	m_texture(NULL),
	m_material(NULL)
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
	m_openGLFunctions = new QOPENGLFUNCTIONS_CLASSNAME();
	m_openGLFunctions->initializeOpenGLFunctions();

	m_mesh = new Mesh(*m_openGLFunctions);
	QList<Vertex> vertices;
	QVector<unsigned int> indices;
	m_texture = new Texture(*m_openGLFunctions, "test.png");
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

	m_rootGameObject->addChild(m_planeObject);
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

	if (m_meshRenderer != NULL)
		delete m_meshRenderer;
	if (m_material != NULL)
		delete m_material;
	if (m_texture != NULL)
		delete m_texture;
	if (m_mesh != NULL)
		delete m_mesh;
	if (m_openGLFunctions != NULL)
		delete m_openGLFunctions;
	m_controller->disconnectFromEvents();
	delete m_controller;
	delete m_rootGameObject;
}
