#-------------------------------------------------
#
# Project created by QtCreator 2017-03-17T00:04:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Engine3D
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
	engine/rendering/mainwindow.cpp \
	engine/rendering/openglwidget.cpp \
	engine/core/scene.cpp \
	game/defaultscene.cpp \
	engine/core/userinput.cpp \
	game/tutorialscene.cpp \
	game/tutorialcontroller.cpp \
	engine/core/vector2f.cpp \
	engine/core/vector3f.cpp \
	engine/core/matrix4f.cpp \
	engine/core/quaternion.cpp \
	engine/rendering/renderutils.cpp \
	engine/rendering/vertex.cpp \
	engine/rendering/mesh.cpp \
	engine/rendering/shader.cpp \
	utils.cpp \
	engine/core/transform.cpp \
	engine/rendering/camera.cpp \
	engine/rendering/texture.cpp \
	engine/rendering/basicshader.cpp \
	engine/rendering/material.cpp \
	engine/rendering/phongshader.cpp \
    engine/components/baselight.cpp \
	engine/components/directionallight.cpp \
	engine/components/attenuation.cpp \
	engine/components/pointlight.cpp \
	game/terrainscene.cpp \
	engine/core/scenewithtimemeasurement.cpp \
	engine/components/spotlight.cpp \
	game/basetutorialscene.cpp \
	game/tutorialscenemonkey.cpp \
	engine/core/coreengine.cpp \
	engine/core/gameobject.cpp \
	engine/components/gamecomponent.cpp \
	game/tutorialscene2.cpp \
	engine/components/meshrenderer.cpp \
	engine/rendering/renderingengine.cpp \
	engine/core/scenewithrootobject.cpp \
	engine/rendering/forwardambientshader.cpp \
	engine/rendering/forwarddirectionalshader.cpp \
	engine/rendering/forwardpointshader.cpp \
	engine/rendering/forwardspotshader.cpp

HEADERS  += engine/rendering/mainwindow.h \
	engine/rendering/openglwidget.h \
	engine/core/scene.h \
	game/defaultscene.h \
	engine/core/userinput.h \
	game/tutorialscene.h \
	game/tutorialcontroller.h \
	engine/core/vector2f.h \
	engine/core/vector3f.h \
	engine/core/matrix4f.h \
	engine/core/quaternion.h \
	engine/rendering/renderutils.h \
	engine/rendering/vertex.h \
	engine/rendering/mesh.h \
	engine/rendering/shader.h \
	utils.h \
	engine/rendering/qopenglfunctions_selector.h \
	engine/core/transform.h \
	engine/rendering/camera.h \
	engine/rendering/texture.h \
	engine/rendering/basicshader.h \
	engine/rendering/material.h \
	engine/rendering/phongshader.h \
    engine/components/baselight.h \
	engine/components/directionallight.h \
	engine/components/attenuation.h \
	engine/components/pointlight.h \
	game/terrainscene.h \
	engine/core/scenewithtimemeasurement.h \
	engine/components/spotlight.h \
	game/basetutorialscene.h \
	game/tutorialscenemonkey.h \
	engine/core/coreengine.h \
	engine/core/gameobject.h \
	engine/components/gamecomponent.h \
	game/tutorialscene2.h \
	engine/components/meshrenderer.h \
	engine/rendering/renderingengine.h \
	engine/core/scenewithrootobject.h \
	engine/rendering/forwardambientshader.h \
	engine/rendering/forwarddirectionalshader.h \
	engine/rendering/forwardpointshader.h \
	engine/rendering/forwardspotshader.h

INCLUDEPATH += $$PWD

FORMS    += engine/rendering/mainwindow.ui

CONFIG += c++11

RESOURCES += \
    resources.qrc

win32: LIBS += -lopengl32

DISTFILES += \
    resources/shaders/basicvertex.vsh \
    resources/shaders/basicfragment.fsh \
    resources/models/box.obj \
    resources/models/monkey.obj \
    resources/textures/test.png \
    resources/shaders/phongvertex.vsh \
    resources/shaders/phongfragment.fsh \
    resources/shaders/forwardambient.vsh \
    resources/shaders/forwardambient.fsh \
    resources/shaders/forwarddirectional.vsh \
    resources/shaders/forwarddirectional.fsh \
    resources/shaders/forwardpoint.vsh \
    resources/shaders/forwardpoint.fsh \
    resources/shaders/forwardspot.fsh \
    resources/shaders/forwardspot.vsh
