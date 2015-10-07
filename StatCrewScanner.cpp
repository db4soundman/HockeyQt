#include "StatCrewScanner.h"
#include <QFile>
StatCrewScanner::StatCrewScanner(HockeyGame* game, QString fileName)
{
    statCrew = new GameXmlUpdater(game, game->getAwayTeam(), game->getHomeTeam());
    inGame = new QTimer();
    breakTime = new QTimer();
    breakTime->setInterval(1000 * 10);
    statFile = fileName;
    inGame->setInterval(1000 * 5);
    isActive = false;
    connect(inGame, SIGNAL(timeout()), this, SLOT(start()));
    connect(breakTime, SIGNAL(timeout()), this, SLOT(start()));
    connect(game, SIGNAL(periodChanged(int)), this, SLOT(toggleScanner(int)));
    connect(game, SIGNAL(clockIsRunning(bool)), this, SLOT(toggleScanner(bool)));
    connect(game, SIGNAL(toggleStatCrew()), this, SLOT(toggleEnabled()));
    connect(this, SIGNAL(statCrewStatus(bool)), game, SIGNAL(statusOfStatCrew(bool)));
    enabled = true;
}

void StatCrewScanner::toggleScanner() {
    if (!isActive) {
        inGame->start();
    }
    else {
        inGame->stop();
    }
}

void StatCrewScanner::run()
{
    if (enabled)
    updateStats();
}

void StatCrewScanner::toggleEnabled()
{
    enabled = !enabled;
    emit statCrewStatus(enabled);
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

void StatCrewScanner::updateStats() {
    QFile file(statFile);
    QXmlSimpleReader r;
    r.setContentHandler(statCrew);
    r.setErrorHandler(statCrew);
    QXmlInputSource src(&file);
    r.parse(src);
}
