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
#include <QDockWidget>
#include <QStackedWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(HockeyGame* game, StandingsGraphic* graphic, CommercialGraphic* comGraphic,
               NchcScoreboardGraphic* confSbGraphic, ScheduleGraphic* scheduleGraphic, SerialConsole* serial, ComparisonGraphic* comparisonGraphic, QWidget *parent = 0);
    ~MainWindow();

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

    QDockWidget leftDock;

    void makeMenu(HockeyGame* game, SerialConsole *console, CommercialGraphic *comGraphic);


    void createAlternateContent();
};

#endif // MAINWINDOW_H
