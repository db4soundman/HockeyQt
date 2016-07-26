#include "MiamiAllAccessHockey.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include "SetupWizard.h"
#include <QDesktopWidget>
#include <QAction>
#include <QPixmap>
#include "GraphicChooser.txt"
#include "SerialConsole.h"

MiamiAllAccessHockey::MiamiAllAccessHockey(int& argc, char* argv[]) :
    QApplication (argc, argv) {
    setApplicationName("Miami All-Access Hockey");
}

MiamiAllAccessHockey::~MiamiAllAccessHockey()
{
    if (usingTricaster) {
        delete tricaster;
    }
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
}

int
MiamiAllAccessHockey::exec() {
    checkAppDirectory();

    // Make vars, create wizard.
    scene = new QGraphicsScene();

    QString awayName, homeName, awayRank, homeRank, homeFile, awayFile, sponsor, announcer,
            goalies, statcrewName, awayLogo, tricasterIp, awayShort, homeShort;
    QColor awayColor, homeColor,  bg;
    int pk, pkopp, ppg, ppopp, port;
    usingTricaster = true;
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
                       &bg, &pk, &pkopp, &ppg, &ppopp, &goalies, &statcrewName, &usingTricaster, &awayLogo,
                       &tricasterIp, &awayShort, &homeShort, &port);
    wizard.exec();
    QRect graphicsScreen = usingTricaster ? QRect(0,0,1920,1080) : desktop.screenGeometry(0);
    QPixmap awayLogoImg = QPixmap::fromImage(getTrimmedLogo(awayLogo));
    game = new HockeyGame(awayName, homeName, awayColor, homeColor,
                          awayFile, homeFile, sponsor, announcer, awayRank,
                          homeRank, graphicsScreen.width() + 1, awayLogoImg, homeShort, awayShort);
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
    commercial = new CommercialGraphic(game, awayLogoImg);
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
        tricaster = new TricasterHandler(tricasterIp, port, tv, bg);
        game->getSb()->setUseTransparency(true);
        connect(scene, SIGNAL(changed(QList<QRectF>)), tricaster, SLOT(updatePortion(QList<QRectF>)));
        connect(game->getSb(), SIGNAL(transparentField(int,int,int,int)), tricaster, SLOT(addAlphaRect(int,int,int,int)));
        connect(game->getSb(), SIGNAL(removeTransparentField(int,int,int,int)), tricaster, SLOT(removeAlphaRect(int,int,int,int)));
        connect(game->getTricasterRefresh(), SIGNAL(timeout()), tricaster, SLOT(start()));
    }
    SerialConsole con;
    con.show();
    return QApplication::exec();
}

QImage MiamiAllAccessHockey::getTrimmedLogo(QString filePath)
{
    int tX, tY, bX, bY;
    tX = (tY = (bX = (bY = -1)));
    QImage src(filePath);
    QColor background = src.pixel(0,0);

    // Find top most pixel
    for (int i = 0; i < src.height() / 2 && tY == -1; i++) {
        for (int j = 0; j < src.width(); j++) {
            if (QColor(src.pixel(j, i)) != background) {
                tY = i;
                break;
            }
        }
    }

    // Find bottom most pixel
    for (int i = src.height() - 1; i > src.height() / 2 && bY == -1; i--) {
        for (int j = 0; j < src.width(); j++) {
            if (QColor(src.pixel(j, i)) != background) {
                bY = i;
                break;
            }
        }
    }

    // Find left most pixel
    for (int i = 0; i < src.width()/2 && tX == -1; i++) {
        for (int j = 0; j < src.height(); j++) {
            if (QColor(src.pixel(i, j)) != background) {
                tX = i;
                break;
            }
        }
    }

    // Find the right most pixel
    for (int i = src.width() - 1; i > src.width()/2 && bX == -1; i--) {
        for (int j = 0; j < src.height(); j++) {
            if (QColor(src.pixel(i, j)) != background) {
                bX = i;
                break;
            }
        }
    }
    QPoint tl(tX, tY);
    QPoint br(bX, bY);
    QRect box(tl, br);
    return src.copy(box);
}
