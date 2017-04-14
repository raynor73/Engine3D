#include "basetutorialscene.h"
#include <engine/rendering/renderutils.h>
#include <QDebug>

BaseTutorialScene::BaseTutorialScene(CoreEngine &coreEngine, UserInput &userInput, QObject *parent) :
	SceneWithTimeMeasurement(parent),
	m_coreEngine(coreEngine),
	m_userInput(userInput)
{
	connect(&m_fpsTimer, &QTimer::timeout, [this]() {
		qDebug() << "FPS" << m_coreEngine.fps();
	});
	m_fpsTimer.start(1000);

	m_camera = new Camera();
	m_transform = new Transform(*m_camera, 70, 0.1, 1000);
	m_controller = new TutorialController(m_userInput);
}

BaseTutorialScene::~BaseTutorialScene()
{
	m_fpsTimer.stop();
	delete m_controller;
	delete m_transform;
	delete m_camera;
}

void BaseTutorialScene::makeOpenGLDependentSetup()
{
	initializeOpenGLFunctions();

	qDebug() << "OpenGL version" << RenderUtils::getOpenGLVersion(*this);
	RenderUtils::initGraphics(*this);
}

void BaseTutorialScene::onOpenGLResized(int width, int height)
{
	m_transform->setDisplaySize(width, height);
	m_controller->setDisplaySize(width, height);
}

void BaseTutorialScene::start()
{
	m_controller->startReadingUserInput();
}

void BaseTutorialScene::stop()
{
	m_controller->stopReadingUserInput();
}

void BaseTutorialScene::update(float dt)
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
}
