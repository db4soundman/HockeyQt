#include "PpCompUI.h"
#include <QVBoxLayout>
#include <QPainter>


PpCompUI::PpCompUI(HockeyGame* game):
    PowerPlayUpdaters(game, false),
    homePpPixmap(game->getComparisonPreview()->getWidth(), game->getComparisonGraphic()->getHeight()),
    awayPpPixmap(game->getComparisonPreview()->getWidth(), game->getComparisonGraphic()->getHeight())
{
    this->game=game;
    QVBoxLayout* myLayout = new QVBoxLayout();
    myLayout->addLayout(getLayout());
    myLayout->addWidget(&previewAwayPp);
    myLayout->addWidget(&previewHomePp);

    connect(&awayGoal, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(&awayGoal, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(&awayFail, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(&awayFail, SIGNAL(clicked()), this, SLOT(updatePreview()));

    connect(&homeGoal, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(&homeGoal, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(&homeFail, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(&homeFail, SIGNAL(clicked()), this, SLOT(updatePreview()));

    comparisonGraphic = game->getComparisonPreview();
    updatePreview();
    setLayout(myLayout);

    connect(game->getAwayTeam(), SIGNAL(rosterChanged()), this, SLOT(updatePreview()));
    connect(game->getHomeTeam(), SIGNAL(rosterChanged()), this, SLOT(updatePreview()));
}

void PpCompUI::updatePreview()
{
    // Order: Away season, home season, away today, home today.
    QList<QString> stats;
    QString ppStat, pkStat;
    HockeyTeam* awayTeam = game->getAwayTeam();
    HockeyTeam* homeTeam = game->getHomeTeam();
    ppStat = QString::number(homeTeam->getPpPct(), 'g', 3) +"%";
    pkStat = QString::number(awayTeam->getPkPct(), 'g', 3) +"%";
    stats.append(pkStat);
    stats.append(ppStat);
    if (homeTeam->getPpoppToday() > 0) {
        stats.append("Today: " + QString::number(awayTeam->getPkToday()) + "-" + QString::number(awayTeam->getPkoppToday()));
        stats.append("Today: " + QString::number(homeTeam->getPpgToday()) + "-" + QString::number(homeTeam->getPpoppToday()));

    }
    comparisonGraphic->prepareStandardComp("PENALTY KILL", "POWER PLAY", stats);
    homePpPixmap.fill(QColor(0,0,0,0));
    awayPpPixmap.fill(QColor(0,0,0,0));

    QPainter painter(&homePpPixmap);
    comparisonGraphic->paintPreview(&painter);

    stats.clear();

    stats.append(QString::number(awayTeam->getPpPct(), 'g', 3) +"%");
    stats.append(QString::number(homeTeam->getPkPct(), 'g', 3) +"%");
    if (awayTeam->getPpoppToday() > 0) {
        stats.append("Today: " + QString::number(awayTeam->getPpgToday()) + "-" + QString::number(awayTeam->getPpoppToday()));
        stats.append("Today: " + QString::number(homeTeam->getPkToday()) + "-" + QString::number(homeTeam->getPkoppToday()));
    }
    comparisonGraphic->prepareStandardComp("POWER PLAY","PENALTY KILL", stats);
    QPainter painter2(&awayPpPixmap);
    comparisonGraphic->paintPreview(&painter2);

    previewAwayPp.setPixmap(awayPpPixmap.scaled(comparisonGraphic->getWidth()/2, comparisonGraphic->getHeight()/2));
    previewHomePp.setPixmap(homePpPixmap.scaled(comparisonGraphic->getWidth()/2, comparisonGraphic->getHeight()/2));
}
