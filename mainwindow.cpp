#include <QPushButton>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "engineconfig.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(EngineConfig::DISPLAY_WIDTH, EngineConfig::DISPLAY_HEIGHT);

    m_openglWidget = new OpenGLWidget(this, EngineConfig::MAX_FPS);
    m_openglWidget->setGeometry(0, 0, EngineConfig::DISPLAY_WIDTH, EngineConfig::DISPLAY_HEIGHT);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_openglWidget;
}
