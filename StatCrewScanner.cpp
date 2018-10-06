#include "StatCrewScanner.h"
#include <QFile>
StatCrewScanner::StatCrewScanner(HockeyGame* game, QString fileName)
{
    statCrew = new GameXmlUpdater(game, game->getAwayTeam(), game->getHomeTeam());
    inGame = new QTimer();
    breakTime = new QTimer();
    breakTime->setInterval(1000 * 10);
    statFile = "http://sidearmstats.com/miamiohio/mhockey/1.xml";
    inGame->setInterval(1000 * 5);
    isActive = false;
    connect(inGame, SIGNAL(timeout()), this, SLOT(start()));
    connect(breakTime, SIGNAL(timeout()), this, SLOT(start()));
    connect(game, SIGNAL(periodChanged(int)), this, SLOT(toggleScanner(int)));
    connect(game, SIGNAL(clockIsRunning(bool)), this, SLOT(toggleScanner(bool)));
    connect(game, SIGNAL(toggleStatCrew()), this, SLOT(toggleEnabled()));
    connect(this, SIGNAL(statCrewStatus(bool)), game, SIGNAL(statusOfStatCrew(bool)));
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(fileIsReady(QNetworkReply*)) );
    enabled = false;
}

void StatCrewScanner::toggleScanner() {

}

void StatCrewScanner::run()
{
    if (enabled)
    getStats();
}

void StatCrewScanner::toggleEnabled()
{
    enabled = !enabled;
    emit statCrewStatus(enabled);
}

void StatCrewScanner::getStats()
{
    manager->get(QNetworkRequest(QUrl(statFile)));
}

void StatCrewScanner::toggleScanner(int pd)
{
    if (pd == 0) {
        inGame->stop();
        breakTime->stop();
        isActive = false;
    }
    else if (pd == 1) {
        inGame->start();
        isActive = true;
    }
}

void StatCrewScanner::toggleScanner(bool clockStatus) {
    if (!clockStatus) {
        breakTime->start();
        inGame->stop();
    }
    else {
        breakTime->stop();
        inGame->start();
    }
}

void StatCrewScanner::updateStats(QNetworkReply * reply) {
//    QFile file(statFile);
    QXmlSimpleReader r;
    r.setContentHandler(statCrew);
    r.setErrorHandler(statCrew);
    QXmlInputSource src;
    src.setData(reply->readAll());
    r.parse(src);
}
