#ifndef MIAMIALLACCESSHOCKEY_H
#define MIAMIALLACCESSHOCKEY_H

#include <QApplication>
#include "HockeyGame.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "MainWindow.h"
#include "StandingsGraphic.h"
#include "CommercialGraphic.h"
#include "NchcScoreboardGraphic.h"

class MiamiAllAccessHockey : public QApplication {
public:
    MiamiAllAccessHockey(int &argc, char *argv[]);

    /**
     * @brief getAppDirPath Gets the file path to the application
     * directory.
     * @return A QString representing the file path to the application
     * directory.
     */
    static QString getAppDirPath();

    static QString getPenaltiesFilePath();

    void checkAppDirectory();

    int exec();

private:
    QGraphicsView* tv;
    QGraphicsScene* scene;
    HockeyGame* game;
    MainWindow* controlPanel;
    StandingsGraphic standings;
    NchcScoreboardGraphic nchcScoreboard;
    CommercialGraphic* commercial;
};

#endif // MIAMIALLACCESSHOCKEY_H
