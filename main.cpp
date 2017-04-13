#include <engine/rendering/mainwindow.h>
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	format.setVersion(3, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(format);

	MainWindow w(800, 600, 60);
	w.show();

	return a.exec();
}
