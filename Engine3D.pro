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
        mainwindow.cpp \
    engineconfig.cpp \
    openglwidget.cpp \
    scene.cpp \
    defaultscene.cpp \
    userinput.cpp \
    tutorialscene.cpp \
    tutorialcontroller.cpp \
    geometry/vector2f.cpp \
    geometry/vector3f.cpp \
    geometry/matrix4f.cpp \
    geometry/quaternion.cpp \
    renderutils.cpp \
    geometry/vertex.cpp \
    graphics/mesh.cpp \
    graphics/shader.cpp \
    utils.cpp \
    graphics/transform.cpp \
    graphics/camera.cpp \
    graphics/texture.cpp \
    graphics/basicshader.cpp \
    graphics/material.cpp \
    graphics/phongshader.cpp

HEADERS  += mainwindow.h \
    engineconfig.h \
    openglwidget.h \
    scene.h \
    defaultscene.h \
    userinput.h \
    tutorialscene.h \
    tutorialcontroller.h \
    geometry/vector2f.h \
    geometry/vector3f.h \
    geometry/matrix4f.h \
    geometry/quaternion.h \
    renderutils.h \
    geometry/vertex.h \
    graphics/mesh.h \
    graphics/shader.h \
    utils.h \
    qopenglfunctions_selector.h \
    graphics/transform.h \
    graphics/camera.h \
    graphics/texture.h \
    graphics/basicshader.h \
    graphics/material.h \
    graphics/phongshader.h

INCLUDEPATH += $$PWD

FORMS    += mainwindow.ui

CONFIG += c++11

RESOURCES += \
    resources.qrc

DISTFILES += \
    resources/shaders/basicvertex.vsh \
    resources/shaders/basicfragment.fsh \
    resources/models/box.obj \
    resources/models/monkey.obj \
    resources/textures/test.png \
    resources/shaders/phongvertex.vsh \
    resources/shaders/phongfragment.fsh
