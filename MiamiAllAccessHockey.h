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
#include "StatCrewScanner.h"
#include "TricasterHandler.h"
#include "Params.h"
#include <QImage>

class MiamiAllAccessHockey : public QApplication {
public:
    MiamiAllAccessHockey(int &argc, char *argv[]);
    ~MiamiAllAccessHockey();
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

    QImage getTrimmedLogo(QString filePath);

private:
    QGraphicsView* tv;
    QGraphicsScene* scene;
    HockeyGame* game;
    MainWindow* controlPanel;
    StandingsGraphic standings;
    NchcScoreboardGraphic nchcScoreboard;
    CommercialGraphic* commercial;
    StatCrewScanner* stats;
    TricasterHandler* tricaster;
    Params params;
    bool usingTricaster;
};

#endif // MIAMIALLACCESSHOCKEY_H
