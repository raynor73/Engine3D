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
game/scene.cpp \
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
engine/rendering/baselight.cpp \
engine/rendering/directionallight.cpp \
engine/rendering/attenuation.cpp \
engine/rendering/pointlight.cpp \
game/terrainscene.cpp \
game/scenewithtimemeasurement.cpp \
engine/rendering/spotlight.cpp \
game/basetutorialscene.cpp \
game/tutorialscenemonkey.cpp \
    engine/core/coreengine.cpp

HEADERS  += engine/rendering/mainwindow.h \
engine/rendering/openglwidget.h \
game/scene.h \
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
engine/rendering/baselight.h \
engine/rendering/directionallight.h \
engine/rendering/attenuation.h \
engine/rendering/pointlight.h \
game/terrainscene.h \
game/scenewithtimemeasurement.h \
engine/rendering/spotlight.h \
game/basetutorialscene.h \
game/tutorialscenemonkey.h \
    engine/core/coreengine.h

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
    resources/shaders/phongfragment.fsh
