#include "basetutorialscene.h"
#include "renderutils.h"
#include <QDebug>

BaseTutorialScene::BaseTutorialScene(OpenGLWidget &openGLWidget, UserInput &userInput, QObject *parent) :
	SceneWithTimeMeasurement(parent),
	m_openGLWidget(openGLWidget),
	m_userInput(userInput)
{
	initializeOpenGLFunctions();

	qDebug() << "OpenGL version" << RenderUtils::getOpenGLVersion(*this);
	RenderUtils::initGraphics(*this);

	m_controller = new TutorialController(m_userInput, openGLWidget.width(), openGLWidget.height());

	connect(&m_fpsTimer, &QTimer::timeout, [this]() {
		qDebug() << "FPS" << m_openGLWidget.fps();
	});
	m_fpsTimer.start(1000);

	m_camera = new Camera();
	m_transform = new Transform(*m_camera, 70, openGLWidget.width(), openGLWidget.height(), 0.1, 1000);
}

BaseTutorialScene::~BaseTutorialScene()
{
	m_fpsTimer.stop();
	delete m_transform;
	delete m_camera;
	delete m_controller;
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
