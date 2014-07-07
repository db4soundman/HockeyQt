#-------------------------------------------------
#
# Project created by QtCreator 2014-06-21T11:33:23
#
#-------------------------------------------------

QT       += core gui
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graphics
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Scoreboard.cpp \
    LowerThird.cpp \
    Clock.cpp \
    HockeyGame.cpp \
    HockeyTeam.cpp \
    HockeyPlayer.cpp \
    SeasonXMLHandler.cpp \
    GameXmlHandler.cpp

HEADERS  += MainWindow.h \
    Scoreboard.h \
    LowerThird.h \
    Clock.h \
    HockeyGame.h \
    HockeyTeam.h \
    HockeyPlayer.h \
    SeasonXMLHandler.h \
    GameXmlHandler.h


RESOURCES += \
    graphics.qrc
