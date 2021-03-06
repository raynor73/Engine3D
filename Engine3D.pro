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
    engineconfig.cpp \
    geometry/vector2f.cpp \
    geometry/vector3f.cpp \
    geometry/matrix4f.cpp \
    geometry/quaternion.cpp \
    renderutils.cpp \
    geometry/vertex.cpp \
    geometry/mesh.cpp \
    graphics/shader.cpp

HEADERS  += \
    engineconfig.h \
    geometry/vector2f.h \
    geometry/vector3f.h \
    geometry/matrix4f.h \
    geometry/quaternion.h \
    renderutils.h \
    geometry/vertex.h \
    geometry/mesh.h \
    graphics/shader.h

FORMS    += mainwindow.ui

CONFIG += c++11

RESOURCES += \
    resources.qrc

DISTFILES += \
    resources/shaders/basicvertex.vsh \
    resources/shaders/basicfragment.fsh

win32: LIBS += -L$$PWD/libs/win/glew-2.0.0/lib/Release/Win32/ -lglew32s
win32: INCLUDEPATH += $$PWD/libs/win/glew-2.0.0/include
win32: DEPENDPATH += $$PWD/libs/win/glew-2.0.0/include

win32: LIBS += -L$$PWD/libs/win/glfw-3.2.1.bin.WIN32/lib-mingw/ -lglfw3
win32: INCLUDEPATH += $$PWD/libs/win/glfw-3.2.1.bin.WIN32/include
win32: DEPENDPATH += $$PWD/libs/win/glfw-3.2.1.bin.WIN32/include

INCLUDEPATH += $$PWD/libs/glm-0.9.8.4

unix:!macx: LIBS += -L$$PWD/libs/glew-2.0.0/lib/ -lGLEW

INCLUDEPATH += $$PWD/libs/glew-2.0.0/include
DEPENDPATH += $$PWD/libs/glew-2.0.0/include

unix:!macx: PRE_TARGETDEPS += $$PWD/libs/glew-2.0.0/lib/libGLEW.a

unix:!macx: LIBS += -L$$PWD/libs/glfw-3.2.1/src/ -lglfw3

INCLUDEPATH += $$PWD/libs/glfw-3.2.1/include
DEPENDPATH += $$PWD/libs/glfw-3.2.1/include

unix:!macx: PRE_TARGETDEPS += $$PWD/libs/glfw-3.2.1/src/libglfw3.a

unix:!macx: LIBS += -lXrandr -lXrender -lXi -lXfixes -lXxf86vm -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp -ldl -lXcursor -lXinerama
