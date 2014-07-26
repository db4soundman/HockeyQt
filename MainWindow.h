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

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(HockeyGame* game, StandingsGraphic* graphic, CommercialGraphic* comGraphic, NchcScoreboardGraphic* confSbGraphic ,QWidget *parent = 0);
    ~MainWindow();

private:
    ControlPanel panel;
    StandingsWidget standingsPanel;
    NchcScoreboardGui nchcGui;

    void makeMenu();
};

#endif // MAINWINDOW_H
