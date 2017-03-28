#include <cmath>
#include <QDebug>
#include <QList>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include "tutorialscene.h"
#include "renderutils.h"
#include "engineconfig.h"
#include "utils.h"

TutorialScene::TutorialScene(OpenGLWidget &openGLWidget, UserInput &userInput, QObject *parent) :
	Scene(parent),
	m_openGLWidget(openGLWidget),
	m_userInput(userInput)
{
	initializeOpenGLFunctions();

	qDebug() << "OpenGL version" << RenderUtils::getOpenGLVersion(*this);
	RenderUtils::initGraphics(*this);

	m_controller = new TutorialController(m_userInput);

	connect(&m_fpsTimer, &QTimer::timeout, [this]() {
		qDebug() << "FPS" << m_openGLWidget.fps();
	});
	m_fpsTimer.start(1000);

	m_mesh = new Mesh(*this);
	Utils::loadMesh("monkey.obj", *m_mesh);

	m_shader = new Shader(*this);
	QString vertexShaderText = Utils::loadShader("basicvertex.vsh");
	m_shader->setVertexShader(vertexShaderText);
	QString fragmentShaderText = Utils::loadShader("basicfragment.fsh");
	m_shader->setFragmentShader(fragmentShaderText);
	m_shader->linkProgram();
	m_shader->addUniform("transform");

	m_camera = new Camera();
	m_transform = new Transform(*m_camera, 70, EngineConfig::DISPLAY_WIDTH,
								EngineConfig::DISPLAY_HEIGHT, 0.1, 1000);
}

TutorialScene::~TutorialScene()
{
	m_fpsTimer.stop();
	delete m_transform;
	delete m_camera;
	delete m_shader;
	delete m_mesh;
	delete m_controller;
}

void TutorialScene::start()
{
	m_controller->startReadingUserInput();
}

void TutorialScene::stop()
{
	m_controller->stopReadingUserInput();
}

static float temp = 0;
void TutorialScene::update()
{
	float dt = 0;
	if (m_deltaTimer.isValid())
		dt = m_deltaTimer.nsecsElapsed() / 1000000000.0f;

	m_deltaTimer.start();

	temp += dt;

	float sinValue = std::sin(temp);

	m_transform->setTranslation(sinValue, 0, 5);
	m_transform->setRotation(0, sinValue * 180, 0);

	float moveAmount = 10 * dt;
	float rotationAmount = 100 * dt;

	if (m_controller->movementDiretion() == TutorialController::MovementDiretion::Forward)
		m_camera->move(m_camera->forward(), moveAmount);
	if (m_controller->movementDiretion() == TutorialController::MovementDiretion::Backward)
		m_camera->move(m_camera->forward(), -moveAmount);

	if (m_controller->strafeDirection() == TutorialController::StrafeDirection::Left)
		m_camera->move(m_camera->calculateLeft(), moveAmount);
	if (m_controller->strafeDirection() == TutorialController::StrafeDirection::Right)
		m_camera->move(m_camera->calculateRight(), moveAmount);

	if (m_controller->pitchDirection() == TutorialController::PitchDirection::LookUp)
		m_camera->rotateX(-rotationAmount);
	if (m_controller->pitchDirection() == TutorialController::PitchDirection::LookDown)
		m_camera->rotateX(rotationAmount);

	if (m_controller->yawDirection() == TutorialController::YawDirection::TurnLeft)
		m_camera->rotateY(-rotationAmount);
	if (m_controller->yawDirection() == TutorialController::YawDirection::TurnRight)
		m_camera->rotateY(rotationAmount);
}

void TutorialScene::render()
{
	RenderUtils::clearScreen(*this);

	m_shader->bind();
	Matrix4f transformation = m_transform->projectedTransformation();
	m_shader->setUniform("transform", transformation);
	m_mesh->draw();
}
