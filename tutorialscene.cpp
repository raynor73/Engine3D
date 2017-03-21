#include <QDebug>
#include <QList>
#include <QFile>
#include <QTextStream>
#include "tutorialscene.h"
#include "renderutils.h"

TutorialScene::TutorialScene(OpenGLWidget &openGLWidget, UserInput &userInput, QObject *parent) :
    Scene(parent),
    m_openGLWidget(openGLWidget),
    m_userInput(userInput)
{
	initializeOpenGLFunctions();

	qDebug() << "OpenGL version" << RenderUtils::getOpenGLVersion(*this);

	m_controller = new TutorialController(m_userInput);
    m_controller->startReadingUserInput();

    connect(&m_fpsTimer, &QTimer::timeout, [this]() {
        qDebug() << "FPS" << m_openGLWidget.fps();
    });
    m_fpsTimer.start(1000);

	m_mesh = new Mesh(*this);
	QList<Vertex> vertices;
	vertices.append(Vertex(Vector3f(0, 0.5f, 0)));
	vertices.append(Vertex(Vector3f(0.5f, 0.5f, 0)));
	vertices.append(Vertex(Vector3f(-0.5f, 0.5f, 0)));
	m_mesh->setVertices(vertices);

	m_shader = new Shader(*this);

	QFile vertexShaderFile(":/resources/shaders/basicvertex.vsh");
	vertexShaderFile.open(QFile::ReadOnly | QFile::Text);
	QTextStream vertexShaderStream(&vertexShaderFile);
	QString vertexShaderText = vertexShaderStream.readAll();
	vertexShaderFile.close();

	QFile fragmentShaderFile(":/resources/shaders/basicfragment.fsh");
	fragmentShaderFile.open(QFile::ReadOnly | QFile::Text);
	QTextStream fragmentShaderStream(&fragmentShaderFile);
	QString fragmentShaderText = fragmentShaderStream.readAll();
	fragmentShaderFile.close();

	m_shader->setVertexShader(vertexShaderText);
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
{
    RenderUtils::initGraphics(*this);
}

void TutorialScene::stop()
{}

void TutorialScene::render()
{
	RenderUtils::clearScreen(*this);

	m_shader->bind();
	m_mesh->draw();
}
