#include "MiamiAllAccessHockey.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include "SetupWizard.h"
#include <QDesktopWidget>
#include <QAction>

MiamiAllAccessHockey::MiamiAllAccessHockey(int& argc, char* argv[]) :
    QApplication (argc, argv) {
    setApplicationName("Miami All-Access Hockey");
}

QString
MiamiAllAccessHockey::getAppDirPath() {
    return QStandardPaths::writableLocation(QStandardPaths::DataLocation);
}

QString
MiamiAllAccessHockey::getPenaltiesFilePath() {
    return QStandardPaths::writableLocation(QStandardPaths::DataLocation)
            + "/penalties.txt";
}

void
MiamiAllAccessHockey::checkAppDirectory() {
    QDir appDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    if (!appDir.exists()) {
        appDir.mkdir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
        QFile penaltiesFile(":/resources/penalties.txt");
        penaltiesFile.copy(QStandardPaths::writableLocation(QStandardPaths::DataLocation)
                           + "/penalties.txt");
    }
}

int
MiamiAllAccessHockey::exec() {
    checkAppDirectory();

    // Make vars, create wizard.
    scene = new QGraphicsScene();

    QString awayName, homeName, awayRank, homeRank, homeFile, awayFile, sponsor, announcer,
            goalies;
    QColor awayColor, homeColor,  bg;
    int pk, pkopp, ppg, ppopp;

    homeColor.setRgb(226, 24, 54);
    bg.setRgb(0,120,0);
    announcer = "Greg Waddell and Drew Davis";
    sponsor = "Miami IMG Sports Network";
    homeName = "MIAMI";
    SetupWizard wizard(&awayName, &homeName, &awayFile, &homeFile, &sponsor,
                       &announcer, &awayRank, &homeRank, &awayColor, &homeColor,
                       &bg, &pk, &pkopp, &ppg, &ppopp, &goalies);
    wizard.exec();
    game = new HockeyGame(awayName, homeName, awayColor, homeColor,
                          awayFile, homeFile, sponsor, announcer, awayRank,
                          homeRank);
    HockeyTeam* team = game->getAwayTeam();
    team->setPk(pk);
    team->setPkopp(pkopp);
    team->setPpg(ppg);
    team->setPpopp(ppopp);
    team->setGoalies(goalies);
    scene->addItem(game->getSb());

    scene->addItem(game->getLt());
    scene->addItem(&standings);
    scene->addItem(&nchcScoreboard);
    commercial = new CommercialGraphic(game);
    scene->addItem(commercial);
    game->getLt()->setX(337 + 409);
    game->getLt()->setY(920);
    game->getSb()->setY(80);
    game->getSb()->setX(409);
    commercial->setY(850);
    //commercial->setX(460);
    tv = new QGraphicsView(scene);


    QDesktopWidget desktop;
    tv->setGeometry(desktop.screenGeometry(1));
    tv->setSceneRect(0, 0,1920, 1080);
    tv->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tv->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Get desktop set up and wizard val later...
    tv->setBackgroundBrush(bg);
    //tv->setFixedSize(1600,900);
    //tv->show();
    tv->setFrameShape(QFrame::NoFrame);
    tv->showFullScreen();

    controlPanel = new MainWindow(game, &standings, commercial, &nchcScoreboard);
    controlPanel->show();
    return QApplication::exec();
}


