#include <QPushButton>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "engineconfig.h"
#include "defaultscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(EngineConfig::DISPLAY_WIDTH, EngineConfig::DISPLAY_HEIGHT);

    m_openglWidget = new OpenGLWidget(this, EngineConfig::MAX_FPS);
    m_openglWidget->setGeometry(0, 0, EngineConfig::DISPLAY_WIDTH, EngineConfig::DISPLAY_HEIGHT);

    connect(m_openglWidget, &OpenGLWidget::openGLReady, [this] () {
        m_scene = new DefaultScene();
        m_openglWidget->setScene(m_scene);
        m_scene->start();
    });
}

MainWindow::~MainWindow()
{
    m_openglWidget->setScene(NULL);

    if (m_scene != NULL) {
        m_scene->stop();
        delete m_scene;
        m_scene = NULL;
    }

    delete m_openglWidget;
    delete ui;
}
