#include "MiamiAllAccessHockey.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include "SetupWizard.h"
#include <QDesktopWidget>
#include <QAction>
#include "GraphicChooser.txt"

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

QString
MiamiAllAccessHockey::getProfilesFilePath() {
    return QStandardPaths::writableLocation(QStandardPaths::DataLocation)
            + "/TeamProfiles";
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
    QDir teamDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation) +"/TeamProfiles");
    if (!teamDir.exists()) {
        teamDir.mkdir(teamDir.absolutePath());
        QFile profiles(":/resources/profiles.txt");
        profiles.copy(QStandardPaths::writableLocation(QStandardPaths::DataLocation) +"/TeamProfiles/profiles.txt");
    }
}

int
MiamiAllAccessHockey::exec() {
    checkAppDirectory();

    // Make vars, create wizard.
    scene = new QGraphicsScene();

    QString awayName, homeName, awayRank, homeRank, homeFile, awayFile, sponsor, announcer,
            goalies, statcrewName, awayLogo, tricasterIp, awayShort, homeShort;
    QColor awayColor, homeColor,  bg;
    int pk, pkopp, ppg, ppopp;
    bool usingTricaster = true;
    homeColor.setRgb(226, 24, 54);
    bg.setRgb(0,120,0);
    announcer = "Greg Waddell and Drew Davis";
    sponsor = "Miami IMG Sports Network | NCHC.tv";
    homeName = "MIAMI";
    homeShort = "MIAMI";
    tricasterIp = "10.44.65.157";
    QDesktopWidget desktop;

    SetupWizard wizard(&awayName, &homeName, &awayFile, &homeFile, &sponsor,
                       &announcer, &awayRank, &homeRank, &awayColor, &homeColor,
                       &bg, &pk, &pkopp, &ppg, &ppopp, &goalies, &statcrewName, &usingTricaster, &awayLogo, &tricasterIp, &awayShort, &homeShort);
    wizard.exec();
    QRect graphicsScreen = usingTricaster ? QRect(0,0,1920,1080) : desktop.screenGeometry(1);
    game = new HockeyGame(awayName, homeName, awayColor, homeColor,
                          awayFile, homeFile, sponsor, announcer, awayRank,
                          homeRank, graphicsScreen.width() + 1, awayLogo, homeShort, awayShort);
    if (usingTricaster)
        bg.setRgb(0,0,0);
//    HockeyTeam* team = game->getAwayTeam();
//    team->setPk(pk);
//    team->setPkopp(pkopp);
//    team->setPpg(ppg);
//    team->setPpopp(ppopp);
//    team->setGoalies(goalies);

    scene->addItem(game->getSb());

    scene->addItem(game->getLt());
    scene->addItem(&standings);
    scene->addItem(&nchcScoreboard);
#ifdef GRADIENT_LOOK
    commercial = new CommercialGraphic(game, graphicsScreen.width(), awayLogo);
    game->getLt()->setX((graphicsScreen.width() / 2) - 214);
#else
    commercial = new CommercialGraphic(game, awayLogo);
    commercial->setX(graphicsScreen.width() / 2 - 500);
    game->getLt()->setX((graphicsScreen.width() / 2) - 500);
#endif
    scene->addItem(commercial);

    game->getLt()->setY(graphicsScreen.height() - 160);
    game->getSb()->setY(60 - 39);
    game->getSb()->setX((graphicsScreen.width() / 2) - (game->getSb()->getRealWidth()/2));
    commercial->setY(graphicsScreen.height() - 230);
    //commercial->setX(460);
    tv = new QGraphicsView(scene);



    tv->setGeometry(graphicsScreen);
    tv->setSceneRect(0, 0,graphicsScreen.width(), graphicsScreen.height());
    tv->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tv->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Get desktop set up and wizard val later...
    tv->setBackgroundBrush(bg);
    //tv->setFixedSize(1600,900);
    //tv->show();
    tv->setFrameShape(QFrame::NoFrame);

    if (!statcrewName.isEmpty())
        stats = new StatCrewScanner(game, statcrewName);

    controlPanel = new MainWindow(game, &standings, commercial, &nchcScoreboard);
    controlPanel->show();
    if (!usingTricaster)
        tv->showFullScreen();
    else {
        tricaster = new TricasterHandler(tricasterIp, tv, bg);
        game->getSb()->setUseTransparency(true);
        connect(scene, SIGNAL(changed(QList<QRectF>)), tricaster, SLOT(updatePortion(QList<QRectF>)));
        connect(game->getSb(), SIGNAL(transparentField(int,int,int,int)), tricaster, SLOT(addAlphaRect(int,int,int,int)));
        connect(game->getSb(), SIGNAL(removeTransparentField(int,int,int,int)), tricaster, SLOT(removeAlphaRect(int,int,int,int)));
        connect(game->getTricasterRefresh(), SIGNAL(timeout()), tricaster, SLOT(start()));
    }
    return QApplication::exec();
}
