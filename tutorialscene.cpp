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
}

TutorialScene::~TutorialScene()
{
	m_fpsTimer.stop();
	m_controller->stopReadingUserInput();
	delete m_controller;
	delete m_mesh;
	delete m_shader;
}

void TutorialScene::start()
{}

void TutorialScene::stop()
{}

void TutorialScene::render()
{
	RenderUtils::clearScreen(*this);

	m_shader->bind();
	m_mesh->draw();
}
