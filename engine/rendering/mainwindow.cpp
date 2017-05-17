#include <QPushButton>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
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

	m_userInput = new UserInput(*m_openglWidget, this);
}

MainWindow::~MainWindow()
{
	delete m_userInput;
	delete m_openglWidget;
	delete ui;
}
