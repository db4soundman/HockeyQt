#-------------------------------------------------
#
# Project created by QtCreator 2014-06-21T11:33:23
#
#-------------------------------------------------


QT       += core gui network serialport widgets
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network
CONFIG += c++11
TARGET = Graphics
TEMPLATE = app
INCLUDEPATH += GUI \
               Wizard \
            Standings \
            NCHCScoreboard \
            GameStatEditors \
            Profiles \
            SerialHandler \
            Schedule \
            GUI2 \
            DevelopmentCode \
            PastGames \
            TextualRoster

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
    Params.cpp \
    Schedule/schedulegui.cpp \
    Schedule/schedulegraphic.cpp \
    Schedule/scheduleentry.cpp \
    ComparisonGraphic.cpp \
    GUI/FaceoffControl.cpp \
    GUI/ComparisonCreator.cpp \
    GUI2/treeitem.cpp \
    GUI2/treemodel.cpp \
    GUI2/GoalPopUI.cpp \
    GUI2/PenaltyPopUI.cpp \
    GUI2/StatPopUI.cpp \
    GUI2/SeasonLtUI.cpp \
    GUI2/PopUI.cpp \
    GUI2/CustomLtUI.cpp \
    GUI2/SogUI.cpp \
    GUI2/FaceoffUI.cpp \
    GUI2/CustomCompUI.cpp \
    GUI2/PpCompUI.cpp \
    GUI2/gamestateui.cpp \
    DevelopmentCode/CGSimulator.cpp \
    PeriodData.cpp \
    GameHistory.cpp \
    PastGames/PastGamesGraphic.cpp \
    PastGames/PastGamesUI.cpp \
    TextualRoster/TextualRosterInput.cpp \
    School.cpp \
    Wizard/TeamSetupPage.cpp \
    Ticker.cpp \
    GUI2/PenaltyUI.cpp \
    identifierl3rd.cpp

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
    Params.h \
    Schedule/schedulegui.h \
    Schedule/schedulegraphic.h \
    Schedule/scheduleentry.h \
    ComparisonGraphic.h \
    GUI/FaceoffControl.h \
    GUI/ComparisonCreator.h \
    GUI2/treeitem.h \
    GUI2/treemodel.h \
    GUI2/GoalPopUI.h \
    GUI2/PenaltyPopUI.h \
    GUI2/StatPopUI.h \
    GUI2/SeasonLtUI.h \
    GUI2/PopUI.h \
    GUI2/CustomLtUI.h \
    GUI2/SogUI.h \
    GUI2/FaceoffUI.h \
    GUI2/CustomCompUI.h \
    GUI2/PpCompUI.h \
    GUI2/gamestateui.h \
    DevelopmentCode/CGSimulator.h \
    PeriodData.h \
    GameHistory.h \
    PastGames/PastGamesGraphic.h \
    PastGames/PastGamesUI.h \
    TextualRoster/TextualRosterInput.h \
    School.h \
    Wizard/TeamSetupPage.h \
    Ticker.h \
    GUI2/PenaltyUI.h \
    identifierl3rd.h


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
    SerialHandler/settingsdialog.ui \
    TreeView.ui
