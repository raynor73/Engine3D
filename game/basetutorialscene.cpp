#include "basetutorialscene.h"
#include <engine/rendering/renderutils.h>
#include <utils.h>
#include <QDebug>

BaseTutorialScene::BaseTutorialScene(UserInput &userInput, QObject *parent) :
	SceneWithTimeMeasurement(parent),
	m_openGLFunctions(NULL),
	m_userInput(userInput),
	m_fpsCounter(0)
{
	connect(&m_fpsTimer, &QTimer::timeout, [this]() {
		qDebug() << "FPS" << m_fpsCounter;
		m_fpsCounter = 0;
	});

	/*m_camera = new Camera();
	m_transform = new Transform(m_camera, 70, 0.1, 1000);*/
	m_controller = new TutorialController(m_userInput);
}

BaseTutorialScene::~BaseTutorialScene()
{
	m_fpsTimer.stop();
	delete m_controller;
	delete m_transform;
	delete m_camera;
	if (m_openGLFunctions != NULL) {
		delete m_openGLFunctions;
		m_openGLFunctions = NULL;
	}
}

void BaseTutorialScene::makeOpenGLDependentSetup()
{
	m_openGLFunctions = new QOPENGLFUNCTIONS_CLASSNAME();
	m_openGLFunctions->initializeOpenGLFunctions();

	/*qDebug() << "OpenGL version" << RenderUtils::getOpenGLVersion(*m_openGLFunctions);
	RenderUtils::initGraphics(*m_openGLFunctions);*/
}

void BaseTutorialScene::onOpenGLResized(int width, int height)
{
	//m_transform->setDisplaySize(width, height);
	m_controller->setDisplaySize(width, height);
}

void BaseTutorialScene::start()
{
//	m_controller->startReadingUserInput();
	m_fpsTimer.start(1000);
}

void BaseTutorialScene::stop()
{
	//m_controller->stopReadingUserInput();
	m_fpsTimer.stop();
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
		m_camera->rotateX(Utils::toRadians(delta.y() * sensitivity));
		m_camera->rotateY(Utils::toRadians(delta.x() * sensitivity));
	}
}

void BaseTutorialScene::render()
{
	m_fpsCounter++;
}
