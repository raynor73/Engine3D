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

	CoreEngine *coreEngine = new CoreEngine(800, 600, 60, "Engine3D");
	//TutorialScene scene(*coreEngine.userInput());
	//TutorialSceneMonkey scene(*coreEngine.userInput());
	//TerrainScene scene(*coreEngine.userInput());
	TutorialScene2 *scene = new TutorialScene2(*coreEngine->userInput());
	coreEngine->setScene(scene);

	int returnCode = a.exec();

	coreEngine->setScene(NULL);
	delete scene;
	delete coreEngine;

	return returnCode;
}
