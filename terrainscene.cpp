#include "terrainscene.h"

TerrainScene::TerrainScene(OpenGLWidget &openGLWidget, UserInput &userInput, QObject *parent) :
	SceneWithTimeMeasurement(parent),
	m_openGLWidget(openGLWidget),
	m_userInput(userInput)
{
	initializeOpenGLFunctions();

	RenderUtils::initGraphics(*this);

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
	phongShader->setDirectionalLight(DirectionalLight(BaseLight(Vector3f(1, 1, 1), 0.8), Vector3f(1, 1, -1)));
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
}

void TerrainScene::start() {}
void TerrainScene::stop() {}
void TerrainScene::render() {}

void TerrainScene::update(float) {}
