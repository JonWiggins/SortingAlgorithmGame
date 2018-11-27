#-------------------------------------------------
#
# Project created by QtCreator 2018-11-25T12:38:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Egame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    sorts.cpp \
    box2dhandler.cpp

HEADERS += \
        mainwindow.h \
    sorts.h \
    box2dhandler.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Below is for Box2D

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Box2DLib/release/ -lBox2D
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Box2DLib/debug/ -lBox2D
else:unix: LIBS += -L$$PWD/Box2DLib/ -lBox2D

INCLUDEPATH += $$PWD/Box2DIncludes
DEPENDPATH += $$PWD/Box2DIncludes

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/Box2DLib/release/libBox2D.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/Box2DLib/debug/libBox2D.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/Box2DLib/release/Box2D.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/Box2DLib/debug/Box2D.lib
else:unix: PRE_TARGETDEPS += $$PWD/Box2DLib/libBox2D.a

# Below is for SFML


unix:!macx: LIBS += -L$$PWD/SFML-2.5.1/lib/ -lsfml-window

INCLUDEPATH += $$PWD/SFML-2.5.1/include
DEPENDPATH += $$PWD/SFML-2.5.1/include


unix:!macx: LIBS += -L$$PWD/SFML-2.5.1/lib/ -lsfml-system

INCLUDEPATH += $$PWD/SFML-2.5.1/include
DEPENDPATH += $$PWD/SFML-2.5.1/include

unix:!macx: LIBS += -L$$PWD/SFML-2.5.1/lib/ -lsfml-graphics

INCLUDEPATH += $$PWD/SFML-2.5.1/include
DEPENDPATH += $$PWD/SFML-2.5.1/include

unix:!macx: LIBS += -L$$PWD/SFML-2.5.1/lib/ -lsfml-audio

INCLUDEPATH += $$PWD/SFML-2.5.1/include
DEPENDPATH += $$PWD/SFML-2.5.1/include

unix:!macx: LIBS += -L$$PWD/SFML-2.5.1/lib/ -lsfml-network

INCLUDEPATH += $$PWD/SFML-2.5.1/include
DEPENDPATH += $$PWD/SFML-2.5.1/include
