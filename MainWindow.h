#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include "HockeyGame.h"
#include "ControlPanel.h"
#include "StandingsGraphic.h"
#include "StandingsWidget.h"
#include "CommercialGraphic.h"
#include "NchcScoreboardGui.h"
#include "NchcScoreboardGraphic.h"
#include "PlayerEditor.h"
#include "TeamEditor.h"
#include "LowerThirdCreator.h"
#include "schedulegraphic.h"
#include "schedulegui.h"
#include "SerialConsole.h"
#include "ComparisonGraphic.h"
#include "ComparisonCreator.h"
#include <QTreeView>
#include "treemodel.h"
#include "SeasonLtUI.h"
#include "PopUI.h"
#include "CustomLtUI.h"
#include <QDockWidget>
#include <QStackedWidget>
#include <QHash>
#include "SogUI.h"
#include "FaceoffUI.h"
#include "CustomCompUI.h"
#include "ClockControls.h"
#include "DisplayControls.h"
#include "PpCompUI.h"
#include "Goalies.h"
#include "gamestateui.h"
#include "PastGamesUI.h"
#include "SeasonXMLHandler.h"
#include "TextualRosterInput.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(HockeyGame* game, StandingsGraphic* graphic, CommercialGraphic* comGraphic,
               NchcScoreboardGraphic* confSbGraphic, ScheduleGraphic* scheduleGraphic, SerialConsole* serial, ComparisonGraphic* comparisonGraphic,
               PastGamesGraphic *pgg, QWidget *parent = 0);
    ~MainWindow();

    void connectWithCG(SerialConsole* con);
    void connectWithSerialSimulator(CGSimulator* console);

private slots:
    void changeScreen(QModelIndex index);
    void switchContent();
    void updateAwayRoster();
    void updateHomeRoster();

private:
    QStackedWidget mainContent, alternateContent;
    ControlPanel panel;
    StandingsWidget standingsPanel;
    NchcScoreboardGui nchcGui;
    PlayerEditor awayPlayerEdit, homePlayerEdit;
    TeamEditor awayEdit, homeEdit;
    LowerThirdCreator ltCreator;
    ScheduleGUI scheduleGui;
    ComparisonCreator compCreator;

    QTreeView treeView;
    TreeModel* model;
    QHash<QString,int> modelMap;

    PopUI homePops, awayPops;
    SeasonLtUI homeLts, awayLts;
    CustomLtUI customLts;
    SogUI sogUi;
    FaceoffUI faceoffUi;
    CustomCompUI customCompUi;
    ClockControls clockControls;
    Goalies goalies;
    PpCompUI ppCompUi;

    QDockWidget leftDock, rightDock, topDock, bottomDock;
    DisplayControls displayControls;
    GameStateUI gameStateUi;
    PastGamesUI awaypgUi, homepgUi;

    TextualRosterInput awayTextInput, homeTextInput;

    SeasonXMLHandler homeXmlHandler, awayXmlHandler;

    void makeMenu(HockeyGame* game, SerialConsole *console, CommercialGraphic *comGraphic);


    void createAlternateContent();
};

#endif // MAINWINDOW_H
