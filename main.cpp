#include <QApplication>
#include <QSurfaceFormat>
#include <engine/core/coreengine.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	CoreEngine(800, 600, 60, "Engine3D");

	return a.exec();
}
