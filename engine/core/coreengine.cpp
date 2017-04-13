#include "coreengine.h"
#include <QSurfaceFormat>
#include <engine/rendering/mainwindow.h>

CoreEngine::CoreEngine(int width, int height, float maxFps, const QString &title, QObject *parent) : QObject(parent)
{
	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	format.setVersion(3, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(format);

	MainWindow w(width, height, maxFps);
	w.setWindowTitle(title);
	w.show();
}
