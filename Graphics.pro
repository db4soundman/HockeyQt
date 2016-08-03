#-------------------------------------------------
#
# Project created by QtCreator 2014-06-21T11:33:23
#
#-------------------------------------------------

QT       += core gui network serialport widgets
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graphics
TEMPLATE = app
INCLUDEPATH += GUI \
               Wizard \
            Standings \
            NCHCScoreboard \
            GameStatEditors \
            Profiles \
            SerialHandler

SOURCES += main.cpp\
        MainWindow.cpp \
    Scoreboard.cpp \
    LowerThird.cpp \
    Clock.cpp \
    HockeyGame.cpp \
    HockeyTeam.cpp \
    HockeyPlayer.cpp \
    SeasonXMLHandler.cpp \
    GameXmlHandler.cpp \
    MiamiAllAccessHockey.cpp \
    GUI/ControlPanel.cpp \
    GUI/DisplayControls.cpp \
    GUI/PowerPlayUpdaters.cpp \
    GUI/PenaltyControl.cpp \
    GUI/SogControl.cpp \
    GUI/ScoreControl.cpp \
    GUI/GameInfo.cpp \
    GUI/ClockControls.cpp \
    GUI/StatDisplayControls.cpp \
    GUI/VisitingGameStatControl.cpp \
    GUI/HomeStatControl.cpp \
    GUI/GoalDisplayWidget.cpp \
    GUI/PenaltyDisplay.cpp \
    GUI/Goalies.cpp \
    GUI/ClockDialog.cpp \
    GUI/PpClockDialog.cpp \
    Wizard/SetupWizard.cpp \
    Wizard/SetupPage.cpp \
    Standings/StandingsEntry.cpp \
    Standings/StandingsGraphic.cpp \
    Standings/StandingsWidget.cpp \
    CommercialGraphic.cpp \
    Wizard/AwayTeamInfo.cpp \
    NCHCScoreboard/NchcScoreEntry.cpp \
    NCHCScoreboard/NchcScoreboardGraphic.cpp \
    NCHCScoreboard/NchcGameGui.cpp \
    NCHCScoreboard/NchcScoreboardGui.cpp \
    GameStatEditors/PlayerEditor.cpp \
    GameStatEditors/TeamEditor.cpp \
    LowerThirdCreator.cpp \
    GameXmlUpdater.cpp \
    StatCrewScanner.cpp \
    TricasterHandler.cpp \
    Profiles/Profile.cpp \
    GUI/CheckboxWidget.cpp \
    SerialHandler/console.cpp \
    SerialHandler/SerialConsole.cpp \
    SerialHandler/settingsdialog.cpp \
    Params.cpp

HEADERS  += MainWindow.h \
    Scoreboard.h \
    LowerThird.h \
    Clock.h \
    HockeyGame.h \
    HockeyTeam.h \
    HockeyPlayer.h \
    SeasonXMLHandler.h \
    GameXmlHandler.h \
    MiamiAllAccessHockey.h \
    GUI/ControlPanel.h \
    GUI/DisplayControls.h \
    GUI/PowerPlayUpdaters.h \
    GUI/PenaltyControl.h \
    GUI/SogControl.h \
    GUI/ScoreControl.h \
    GUI/GameInfo.h \
    GUI/ClockControls.h \
    GUI/StatDisplayControls.h \
    GUI/VisitingGameStatControl.h \
    GUI/HomeStatControl.h \
    GUI/GoalDisplayWidget.h \
    GUI/PenaltyDisplay.h \
    GUI/Goalies.h \
    GUI/ClockDialog.h \
    GUI/PpClockDialog.h \
    Wizard/SetupWizard.h \
    Wizard/SetupPage.h \
    Standings/StandingsEntry.h \
    Standings/StandingsGraphic.h \
    Standings/StandingsWidget.h \
    CommercialGraphic.h \
    Wizard/AwayTeamInfo.h \
    NCHCScoreboard/NchcScoreEntry.h \
    NCHCScoreboard/NchcScoreboardGraphic.h \
    NCHCScoreboard/NchcGameGui.h \
    NCHCScoreboard/NchcScoreboardGui.h \
    GameStatEditors/PlayerEditor.h \
    GameStatEditors/TeamEditor.h \
    LowerThirdCreator.h \
    GameXmlUpdater.h \
    StatCrewScanner.h \
    TricasterHandler.h \
    AirSend_api.h \
    Profiles/Profile.h \
    GUI/CheckboxWidget.h \
    SerialHandler/console.h \
    SerialHandler/SerialConsole.h \
    SerialHandler/settingsdialog.h \
    Params.h


RESOURCES += \
    graphics.qrc \
    terminal.qrc

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
unix|win32: LIBS += -L$$PWD/ -lProcessingAirSendx86

DISTFILES += \
    GraphicChooser.txt

FORMS += \
    SerialHandler/SerialConsole.ui \
    SerialHandler/settingsdialog.ui
