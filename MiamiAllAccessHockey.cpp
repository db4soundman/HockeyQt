#include "MiamiAllAccessHockey.h"
#include "Processing.NDI.Lib.h"
#include "School.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include "SetupWizard.h"
#include <QDesktopWidget>
#include <QAction>
#include <QTextStream>
#include "GraphicChooser.txt"
#include "SerialConsole.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include "globals.h"

School MiamiAllAccessHockey::awaySchool = School();
School MiamiAllAccessHockey::homeSchool = School();

MiamiAllAccessHockey::MiamiAllAccessHockey(int& argc, char* argv[]) :
    QApplication (argc, argv) {
    setApplicationName("Miami Hockey");
}

MiamiAllAccessHockey::~MiamiAllAccessHockey()
{
    if (usingTricaster) {
        delete tricaster;
    }
}

QString
MiamiAllAccessHockey::getAppDirPath() {
    return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + applicationName().replace(" ", "");
}
QString
MiamiAllAccessHockey::getPenaltiesFilePath() {
    return getAppDirPath() + "/penalties.txt";
}

QPixmap MiamiAllAccessHockey::getImgFromResources(QString name, int maxHeight, int maxWidth)
{
    QPixmap img(name);
    img = img.scaledToHeight(maxHeight, Qt::SmoothTransformation);

    if (img.width() > maxWidth) {
        return img.scaledToWidth(maxWidth, Qt::SmoothTransformation);
    }
    return img;
}

QPixmap MiamiAllAccessHockey::getImgFromESPN(QString name, int maxHeight, int maxWidth)
{
    QPixmap img = QPixmap::fromImage(getTrimmedLogo(name));
    img = img.scaledToHeight(maxHeight, Qt::SmoothTransformation);

    if (img.width() > maxWidth) {
        return img.scaledToWidth(maxWidth, Qt::SmoothTransformation);
    }
    return img;
}

void
MiamiAllAccessHockey::checkAppDirectory() {
    QDir appDir(getAppDirPath());
    if (!appDir.exists()) {
        appDir.mkdir(getAppDirPath());
    }

    QFile penalties(getPenaltiesFilePath());
    if (!penalties.exists()) {
        QFile penaltiesSrc(":/resources/penalties.txt");
        penalties.open(QIODevice::ReadWrite);
        penaltiesSrc.open(QIODevice::ReadOnly);
        //settings.copy(getAppDirPath()+"/settings.txt");
        QTextStream out(&penalties);
        penaltiesSrc.open(QIODevice::ReadOnly);
        QTextStream in(&penaltiesSrc);
        out << in.readAll();
        penalties.close();
    }


    QFile settings(getAppDirPath()+"/settings.txt");
    if (!settings.exists()) {
        QFile settingsSrc(":/resources/settings");
        settings.open(QIODevice::ReadWrite);
        settingsSrc.open(QIODevice::ReadOnly);
        //settings.copy(getAppDirPath()+"/settings.txt");
        QTextStream out(&settings);
        settingsSrc.open(QIODevice::ReadOnly);
        QTextStream in(&settingsSrc);
        out << in.readAll();
        settings.close();
    }

    QFile standingsFile(getAppDirPath() + "/standings.txt");
    if (!standingsFile.exists()) {
        QFile standingsSrc(":/resources/standings.txt");
        standingsFile.open(QIODevice::ReadWrite);
        QTextStream out(&standingsFile);
        standingsSrc.open(QIODevice::ReadOnly);
        QTextStream in(&standingsSrc);
        out << in.readAll();
        //standingsSrc.copy(getAppDirPath() + "/standings.txt");
        standingsFile.close();
    }

    QFile scheduleFile(getAppDirPath() + "/schedule.csv");
    if (!scheduleFile.exists()) {
        QFile scheduleSrc(":/resources/schedule.csv");
        scheduleFile.open(QIODevice::ReadWrite);
        QTextStream out(&scheduleFile);
        scheduleSrc.open(QIODevice::ReadOnly);
        QTextStream in(&scheduleSrc);
        out << in.readAll();
        //scheduleSrc.copy(getAppDirPath() + "/schedule.txt");
        scheduleFile.close();
    }

    params = Params((getAppDirPath() + "/settings.txt").toStdString());
}

int
MiamiAllAccessHockey::exec() {
    checkAppDirectory();
    NDIlib_send_create_t tricaster_ndi;
    tricaster_ndi.p_ndi_name = "NCHC.tv Gfx";
    tricaster_ndi.p_groups = NULL;
    NDIlib_send_instance_t tricaster_sender = NDIlib_send_create(&tricaster_ndi);
    // Make vars, create wizard.
    scene = new QGraphicsScene();

    QString awayRank, homeRank, homeFile, awayFile, sponsor,
            goalies, statcrewName, tricasterIp;
    QColor bg;
    int pk, pkopp, ppg, ppopp, port, hpk, hpkopp, hppg, hppopp;
    MiamiAllAccessHockey::homeSchool = School::getSchoolFromESPN("MIAMI_OH");
    MiamiAllAccessHockey::awaySchool = School::getSchoolFromESPN("WESTERN_MICHIGAN");
    homeSchool.setShortName("MIAMI");
    homeSchool.setTitle("MIAMI");
    homeSchool.setFullName("MIAMI");
    awaySchool.setShortName("WMU");
    awaySchool.setTitle("W. MICHIGAN");
    awaySchool.setFullName("W. MICHIGAN");
    usingTricaster = true;

    bg.setRgb(0,120,0);
    //announcer = params.stringValue("ANNOUNCER");
    sponsor = params.stringValue("SPONSOR");
    tricasterIp = params.stringValue("IP");
    QDesktopWidget desktop;

    SetupWizard wizard(&awayFile, &homeFile, &sponsor,
                       &awayRank, &homeRank, &bg, &pk, &pkopp, &ppg, &ppopp, &goalies, &statcrewName, &usingTricaster,
                       &tricasterIp, &port, &hpk, &hpkopp, &hppg, &hppopp);
    wizard.exec();
    QRect graphicsScreen = usingTricaster ? QRect(0,0,1920,1080) : desktop.screenGeometry(0);
    if (MiamiAllAccessHockey::awaySchool.getShortName().isEmpty()) {
        MiamiAllAccessHockey::awaySchool.setShortName(MiamiAllAccessHockey::awaySchool.getFullName());
    }
    Globals::hashtag = "#" + MiamiAllAccessHockey::awaySchool.getShortName() + "vs" + MiamiAllAccessHockey::homeSchool.getShortName();
    game = new HockeyGame(awayFile, homeFile, sponsor, awayRank,
                          homeRank, graphicsScreen.width() + 1);
    if (usingTricaster)
        bg.setRgb(0,0,0);

    if (awayFile.isEmpty()) {
        HockeyTeam* team = game->getAwayTeam();
        team->setPk(pk);
        team->setPkopp(pkopp);
        team->setPpg(ppg);
        team->setPpopp(ppopp);
        team->setGoalies(goalies);
    }
    if (homeFile.isEmpty()) {
        HockeyTeam* team = game->getHomeTeam();
        team->setPk(hpk);
        team->setPkopp(hpkopp);
        team->setPpg(hppg);
        team->setPpopp(hppopp);
    }
    pgg = new PastGamesGraphic(game->getHomeTeam(), game->getAwayTeam());
    pgg->setX(100);
    pgg->setY(650);
    scene->addItem(pgg);
    scene->addItem(game->getSb());

    scene->addItem(game->getLt());
    standings.setY(150);
    scene->addItem(&standings);
    scene->addItem(&nchcScoreboard);
    scene->addItem(&scheduleGraphic);
#ifdef GRADIENT_LOOK
    commercial = new CommercialGraphic(game, graphicsScreen.width(), awayLogo);
    game->getLt()->setX((graphicsScreen.width() / 2) - 214);
#else
    commercial = new CommercialGraphic(game);
    commercial->setX(graphicsScreen.width() / 2 - (commercial->getWidth() / 2));
    game->getLt()->setX((graphicsScreen.width() / 2) - 500);
#endif
    scene->addItem(commercial);
    comparisonGraphic = new ComparisonGraphic();
    comparisonGraphic->setX((graphicsScreen.width() / 2) - 500);
    comparisonGraphic->setY(graphicsScreen.height() - 198);
    scene->addItem(comparisonGraphic);
    game->setComparisonGraphic(comparisonGraphic);
    scheduleGraphic.setX(100);
    scheduleGraphic.setY(650);
    game->getLt()->setY(graphicsScreen.height() - 160);
    game->getSb()->setY(60 - 39);
    game->getSb()->setX((graphicsScreen.width() / 2) - (game->getSb()->getRealWidth()/2));
    commercial->setY(graphicsScreen.height() - 280);

    ticker.setX(0);
    ticker.setY(1080-ticker.rect().height());
    scene->addItem(&ticker);

    idGraphic.setX((1920 - idGraphic.getWidth())/2);
    idGraphic.setY(900);
    scene->addItem(&idGraphic);


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

    SerialConsole con;
    controlPanel = new MainWindow(game, &standings, commercial, &nchcScoreboard, &scheduleGraphic, &con, comparisonGraphic, pgg, &ticker, &idGraphic);
    controlPanel->show();
    game->connectWithSerialHandler(&con);

    if (!usingTricaster)
        tv->showFullScreen();
    else {
        previewWindow = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout();
        tricaster = new NDITricasterHandler(tv, bg, &tricaster_sender);
        previewSb = new QGraphicsView(scene);
        previewSb->setBackgroundBrush(QColor(100,100,100));
        previewSb->setSceneRect(game->getSb()->x(), game->getSb()->y(), game->getSb()->getRealWidth(), 150);
        layout->addWidget(previewSb);
        previewLt = new QGraphicsView(scene);
        previewLt->setBackgroundBrush(QColor(100,100,100));
        previewLt->setSceneRect(300, 700, commercial->getWidth(), 400);
        layout->addWidget(previewLt);
        previewWindow->setLayout(layout);
        previewWindow->setWindowTitle("Graphic View");
        previewWindow->show();
        game->getSb()->setUseTransparency(true);
        connect(scene, SIGNAL(changed(QList<QRectF>)), tricaster, SLOT(updatePortion(QList<QRectF>)));
        connect(game->getSb(), SIGNAL(transparentField(int,int,int,int)), tricaster, SLOT(addAlphaRect(int,int,int,int)));
        connect(game->getSb(), SIGNAL(removeTransparentField(int,int,int,int)), tricaster, SLOT(removeAlphaRect(int,int,int,int)));
        connect(game->getTricasterRefresh(), SIGNAL(timeout()), tricaster, SLOT(start()));
        connect(game->getSb(), SIGNAL(addNoTransparencyZone(QRect)), tricaster, SLOT(addNoTransparencyZone(QRect)));
        connect(commercial, SIGNAL(addNoTransparencyZone(QRect)), tricaster, SLOT(addNoTransparencyZone(QRect)));
        connect(game->getSb(),SIGNAL(removeNoTransparencyZone(QRect)), tricaster, SLOT(removeNoTransparencyZone(QRect)));
        connect(commercial,SIGNAL(removeNoTransparencyZone(QRect)), tricaster, SLOT(removeNoTransparencyZone(QRect)));

        connect(game->getLt(), SIGNAL(addNoTransparencyZone(QRect)), tricaster, SLOT(addNoTransparencyZone(QRect)));
        connect(game->getLt(),SIGNAL(removeNoTransparencyZone(QRect)), tricaster, SLOT(removeNoTransparencyZone(QRect)));

        connect(comparisonGraphic, SIGNAL(addNoTransparencyZone(QRect)), tricaster, SLOT(addNoTransparencyZone(QRect)));
        connect(comparisonGraphic,SIGNAL(removeNoTransparencyZone(QRect)), tricaster, SLOT(removeNoTransparencyZone(QRect)));
        connect(pgg, SIGNAL(addNoTransparencyZone(QRect)), tricaster, SLOT(addNoTransparencyZone(QRect)));
        connect(pgg,SIGNAL(removeNoTransparencyZone(QRect)), tricaster, SLOT(removeNoTransparencyZone(QRect)));
        connect(this, SIGNAL(aboutToQuit()), tricaster, SLOT(closing()));
        tricaster->start();
    }

    con.show();
#ifdef DEBUG
    game->connectWithSerialSimulator(&cgSimulator);
    controlPanel->connectWithSerialSimulator(&cgSimulator);
    cgSimulator.show();
    cgSimulator.sendCgConnected();
#endif
    return QApplication::exec();
}

QImage MiamiAllAccessHockey::getTrimmedLogo(QString filePath)
{
    if (filePath.endsWith("NOESPN")) {
        filePath = filePath.left(filePath.indexOf("NOESPN"));
        QImage src(filePath);
        return src;
    }
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
