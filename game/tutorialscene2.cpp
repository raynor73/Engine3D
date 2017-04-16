#include "tutorialscene2.h"
#include <QDebug>
#include <engine/rendering/renderutils.h>

TutorialScene2::TutorialScene2(UserInput &userInput, QObject *parent) :
	SceneWithTimeMeasurement(parent),
	m_openGLFunctions(NULL),
	m_mesh(NULL),
	m_texture(NULL),
	m_material(NULL),
	m_fpsCounter(0)
{
	connect(&m_fpsTimer, &QTimer::timeout, [this]() {
		qDebug() << "FPS" << m_fpsCounter;
		m_fpsCounter = 0;
	});

	m_camera = new Camera();
	m_root = new GameObject(m_camera, 70, 0.1, 1000);
	m_controller = new TutorialController(userInput);
}

void TutorialScene2::onOpenGLResized(int width, int height)
{
	m_root->transform()->setDisplaySize(width, height);
	m_controller->setDisplaySize(width, height);
	//m_root->transform()->setTranslation(0, 1, 0);
}

void TutorialScene2::start()
{
	m_controller->startReadingUserInput();
	m_fpsTimer.start(1000);
}

void TutorialScene2::stop()
{
	m_controller->stopReadingUserInput();
	m_fpsTimer.stop();
}

void TutorialScene2::makeOpenGLDependentSetup()
{
	m_openGLFunctions = new QOPENGLFUNCTIONS_CLASSNAME();
	m_openGLFunctions->initializeOpenGLFunctions();

	qDebug() << "OpenGL version" << RenderUtils::getOpenGLVersion(*m_openGLFunctions);
	RenderUtils::initGraphics(*m_openGLFunctions);

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

	m_meshRenderer = new MeshRenderer(*m_openGLFunctions, m_mesh, m_material);
	m_root->addComponent(m_meshRenderer);
}

void TutorialScene2::update(float dt)
{
	float sensitivity = 0.5;

	m_controller->updatePointer();

	float moveAmount = 10 * dt;

	if (m_controller->movementDiretion() == TutorialController::MovementDiretion::Forward)
		m_camera->move(m_camera->forward(), moveAmount);
	if (m_controller->movementDiretion() == TutorialController::MovementDiretion::Backward)
		m_camera->move(m_camera->forward(), -moveAmount);

	if (m_controller->strafeDirection() == TutorialController::StrafeDirection::Left)
		m_camera->move(m_camera->calculateLeft(), moveAmount);
	if (m_controller->strafeDirection() == TutorialController::StrafeDirection::Right)
		m_camera->move(m_camera->calculateRight(), moveAmount);

	if (m_controller->isGrabPointerRequested())
		m_controller->grabPointer();

	if (m_controller->isReleasePointerRequested())
		m_controller->releasePointer();

	if (m_controller->isPointerGrabbed()) {
		QPoint delta = m_controller->pointerDelta();
		m_camera->rotateX(delta.y() * sensitivity);
		m_camera->rotateY(delta.x() * sensitivity);
	}

	m_root->update(dt);
}

void TutorialScene2::render()
{
	m_fpsCounter++;
	m_root->render();
}

TutorialScene2::~TutorialScene2()
{
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
	delete m_controller;
	delete m_root;
	delete m_camera;
	m_fpsTimer.stop();
}
