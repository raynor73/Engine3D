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
#include "geometry/vector2f.h"
#include "graphics/phongshader.h"

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
	QList<Vertex> vertices;
	vertices += Vertex(Vector3f(-1, -1, 0), Vector2f(0, 0));
	vertices += Vertex(Vector3f(0, 1, 0), Vector2f(0.5, 0));
	vertices += Vertex(Vector3f(1, -1, 0), Vector2f(1, 0));
	vertices += Vertex(Vector3f(0, -1, 1), Vector2f(0, 0.5));
	QVector<unsigned int> indices;
	indices += 3;
	indices += 1;
	indices += 0;
	indices += 2;
	indices += 1;
	indices += 3;
	indices += 0;
	indices += 1;
	indices += 2;
	indices += 0;
	indices += 2;
	indices += 3;
	m_mesh->setVertices(vertices, indices);
	//Utils::loadMesh("monkey.obj", *m_mesh);

	Texture *texture = Utils::newTexture(*this, "test.png");
	m_material = new Material(*texture, Vector3f(1, 1, 1));
	delete texture;

	m_shader = new PhongShader(*this);
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
	delete m_material;
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
	float sensitivity = 0.5;

	float dt = 0;
	if (m_deltaTimer.isValid())
		dt = m_deltaTimer.nsecsElapsed() / 1000000000.0f;

	m_deltaTimer.start();

	m_controller->updatePointer();

	temp += dt;

	float sinValue = std::sin(temp);

	m_transform->setTranslation(sinValue, 0, 5);
	m_transform->setRotation(0, sinValue * 180, 0);

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

void TutorialScene::render()
{
	RenderUtils::clearScreen(*this);

	m_shader->bind();
	m_shader->updateUniforms(m_transform->transformation(), m_transform->projectedTransformation(), *m_material);
	m_mesh->draw();
}
