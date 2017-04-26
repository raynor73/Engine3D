#include <QApplication>
#include <QSurfaceFormat>
#include <engine/core/coreengine.h>
#include <game/tutorialscene.h>
#include <game/tutorialscenemonkey.h>
#include <game/terrainscene.h>
#include <game/tutorialscene2.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	CoreEngine coreEngine(800, 600, 60, "Engine3D");
	//TutorialScene scene(*coreEngine.userInput());
	//TutorialSceneMonkey scene(*coreEngine.userInput());
	//TerrainScene scene(*coreEngine.userInput());
	TutorialScene2 scene(coreEngine);
	coreEngine.setScene(&scene);

	return a.exec();
}
