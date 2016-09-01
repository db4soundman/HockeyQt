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

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(HockeyGame* game, StandingsGraphic* graphic, CommercialGraphic* comGraphic,
               NchcScoreboardGraphic* confSbGraphic, ScheduleGraphic* scheduleGraphic, QWidget *parent = 0);
    ~MainWindow();

private:
    ControlPanel panel;
    StandingsWidget standingsPanel;
    NchcScoreboardGui nchcGui;
    PlayerEditor awayPlayerEdit, homePlayerEdit;
    TeamEditor awayEdit, homeEdit;
    LowerThirdCreator ltCreator;
    ScheduleGUI scheduleGui;

    void makeMenu(HockeyGame* game);
};

#endif // MAINWINDOW_H
