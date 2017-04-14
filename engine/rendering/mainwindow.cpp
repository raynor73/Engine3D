#include <QPushButton>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <game/tutorialscene.h>
#include <game/terrainscene.h>
#include <game/tutorialscenemonkey.h>

MainWindow::MainWindow(int initialWidth, int initialHeight, float maxFps, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setFixedSize(initialWidth, initialHeight);

	m_openglWidget = new OpenGLWidget(this, maxFps);
	m_openglWidget->setGeometry(0, 0, width(), height());

	// TODO Think about if QOpenGLWidget::paintGL can be run before below connection
	//connect(m_openglWidget, &OpenGLWidget::openGLReady, this, &MainWindow::onOpenGLReady);

	m_userInput = new UserInput(*m_openglWidget, this);
}

/*void MainWindow::onOpenGLReady()
{
	//m_scene = new TutorialSceneMonkey(*m_openglWidget, *m_userInput);
	m_scene = new TutorialScene(*m_openglWidget, *m_userInput);
	//m_scene = new TerrainScene(*m_openglWidget, *m_userInput);
	m_scene->start();
	m_openglWidget->setScene(m_scene);
	disconnect(m_openglWidget, &OpenGLWidget::openGLReady, this, &MainWindow::onOpenGLReady);
}*/

MainWindow::~MainWindow()
{
	/*m_openglWidget->setScene(NULL);

	if (m_scene != NULL) {
		m_scene->stop();
		delete m_scene;
		m_scene = NULL;
	}*/

	delete m_userInput;
	delete m_openglWidget;
	delete ui;
}
