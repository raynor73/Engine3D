#include <cmath>
#include <QDebug>
#include <QList>
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
	m_controller->startReadingUserInput();

	connect(&m_fpsTimer, &QTimer::timeout, [this]() {
		qDebug() << "FPS" << m_openGLWidget.fps();
	});
	m_fpsTimer.start(1000);

	m_mesh = new Mesh(*this);
	QList<Vertex> vertices;
	vertices.append(Vertex(Vector3f(0, 1, 0)));
	vertices.append(Vertex(Vector3f(1, -1, 0)));
	vertices.append(Vertex(Vector3f(-1, -1, 0)));
	m_mesh->setVertices(vertices);

	m_shader = new Shader(*this);

	QString vertexShaderText = Utils::loadShader("basicvertex.vsh");
	m_shader->setVertexShader(vertexShaderText);

	QString fragmentShaderText = Utils::loadShader("basicfragment.fsh");
	m_shader->setFragmentShader(fragmentShaderText);

	m_shader->linkProgram();

	m_shader->addUniform("transform");

	m_transform = new Transform();
}

TutorialScene::~TutorialScene()
{
	m_fpsTimer.stop();
	m_controller->stopReadingUserInput();
	delete m_transform;
	delete m_shader;
	delete m_mesh;
	delete m_controller;
}

void TutorialScene::start()
{}

void TutorialScene::stop()
{}

static float temp = 0;
void TutorialScene::update()
{
	float dt = 0;
	if (m_deltaTimer.isValid())
		dt = m_deltaTimer.nsecsElapsed() / 1000000000.0f;

	m_deltaTimer.start();

	temp += dt;
	m_transform->setTranslation(std::sin(temp), 0, 0);
	m_transform->setRotation(0, 0, std::sin(temp) * 180);
}

void TutorialScene::render()
{
	RenderUtils::clearScreen(*this);

	m_shader->bind();
	Matrix4f transformation = m_transform->transformation();
	m_shader->setUniform("transform", transformation);
	m_mesh->draw();
}
