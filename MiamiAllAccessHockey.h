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
#include "schedulegraphic.h"
#include "Params.h"
#include <QImage>
#include <QPixmap>

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

    static QPixmap getImgFromResources(QString name, int maxHeight, int maxWidth = 1920);
    static QPixmap getImgFromESPN(QString name, int maxHeight, int maxWidth = 1920);

    void checkAppDirectory();

    int exec();

    static QImage getTrimmedLogo(QString filePath);

private:
    QGraphicsView* tv;
    QGraphicsScene* scene;
    HockeyGame* game;
    MainWindow* controlPanel;
    StandingsGraphic standings;
    NchcScoreboardGraphic nchcScoreboard;
    ScheduleGraphic scheduleGraphic;
    CommercialGraphic* commercial;
    StatCrewScanner* stats;
    TricasterHandler* tricaster;
    Params params;
    bool usingTricaster;
};

#endif // MIAMIALLACCESSHOCKEY_H
