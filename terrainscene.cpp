#include "terrainscene.h"
#include "renderutils.h"
#include <QDebug>
#include "utils.h"
#include <graphics/directionallight.h>
#include <graphics/phongshader.h>
#include "engineconfig.h"

TerrainScene::TerrainScene(OpenGLWidget &openGLWidget, UserInput &userInput, QObject *parent) :
	SceneWithTimeMeasurement(parent),
	m_openGLWidget(openGLWidget),
	m_userInput(userInput)
{
	initializeOpenGLFunctions();

	RenderUtils::initGraphics(*this);

	m_controller = new TutorialController(m_userInput);

	connect(&m_fpsTimer, &QTimer::timeout, [this]() {
		qDebug() << "FPS" << m_openGLWidget.fps();
	});
	m_fpsTimer.start(1000);

	m_mesh = new Mesh(*this);
	QList<Vertex> vertices;
	QVector<unsigned int> indices;
	m_material = new Material(Vector3f(1, 1, 1), 1, 8);

	Utils::loadMesh("terrain0.obj", *m_mesh, true);
	m_material = new Material(Vector3f(1, 1, 1));

	m_camera = new Camera();

	PhongShader *phongShader = new PhongShader(*this, m_camera);
	phongShader->setAmbientLight(Vector3f(0.1, 0.1, 0.1));
	phongShader->setDirectionalLight(DirectionalLight(BaseLight(Vector3f(1, 1, 1), 0.8),
													  Vector3f(1, 1, -1)));
	m_shader = phongShader;

	m_transform = new Transform(*m_camera, 70, EngineConfig::DISPLAY_WIDTH,
								EngineConfig::DISPLAY_HEIGHT, 0.1, 1000);
}

TerrainScene::~TerrainScene()
{
	m_fpsTimer.stop();
	delete m_transform;
	delete m_camera;
	delete m_shader;
	delete m_material;
	delete m_mesh;
	delete m_controller;
}

void TerrainScene::start()
{
	m_controller->startReadingUserInput();
}

void TerrainScene::stop()
{
	m_controller->stopReadingUserInput();
}

void TerrainScene::update(float dt)
{
	float sensitivity = 0.5;

	m_controller->updatePointer();

	m_transform->setTranslation(0, -1, 5);

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

void TerrainScene::render()
{
	RenderUtils::clearScreen(*this);

	m_shader->bind();
	m_shader->updateUniforms(m_transform->transformation(), m_transform->projectedTransformation(),
							 *m_material);
	m_mesh->draw();
}
