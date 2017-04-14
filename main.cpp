#include <QApplication>
#include <QSurfaceFormat>
#include <engine/core/coreengine.h>
#include <game/tutorialscene.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	CoreEngine(800, 600, 60, "Engine3D");
	//TutorialScene scene()

	return a.exec();
}
