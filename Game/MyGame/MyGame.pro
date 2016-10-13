#-------------------------------------------------
#
# Project created by QtCreator 2016-10-10T13:54:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyGame
TEMPLATE = app


SOURCES += main.cpp \
    Game.cpp \
    Tile.cpp \
    Board.cpp \
    Button.cpp

HEADERS  += \
    Game.h \
    Tile.h \
    Board.h \
    Button.h

RESOURCES += \
    img.qrc
