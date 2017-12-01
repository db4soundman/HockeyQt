#include "Goalies.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

Goalies::Goalies(HockeyGame* game) {
    this->game=game;
    QHBoxLayout* myLayout = new QHBoxLayout();
    QVBoxLayout* away = new QVBoxLayout();
    away->addWidget(new QLabel(game->getAwayTri()));
    awayGoalie.addItems(game->getAwayTeam()->getGuiNames());
    awayGoalie.addItem("EMPTY NET");
    away->addWidget(&awayGoalie);
    awayLt.setText("Game Lower Third");
    awaySB.setText("Game Stat Bar");
    away->addWidget(&awaySeason);
    away->addWidget(&awayLt);
    away->addWidget(&awaySB);
    awaySeason.setText("Season Lower Third");

    QVBoxLayout* home = new QVBoxLayout();
    home->addWidget(new QLabel(game->getHomeTri()));
    homeGoalie.addItems(game->getHomeTeam()->getGuiNames());
    homeGoalie.addItem("EMPTY NET");
    home->addWidget(&homeGoalie);
    homeLt.setText("Game Lower Third");
    homeSB.setText("Game Stat Bar");
    home->addWidget(&homeSeason);
    home->addWidget(&homeLt);
    home->addWidget(&homeSB);
    homeSeason.setText("Season Lower Third");

    myLayout->addLayout(away);
    myLayout->addLayout(home);

    setLayout(myLayout);

    connect(&awayGoalie, SIGNAL(currentIndexChanged(int)),
            game->getAwayTeam(), SLOT(setGoalie(int)));
    connect(&homeGoalie, SIGNAL(currentIndexChanged(int)),
            game->getHomeTeam(), SLOT(setGoalie(int)));
    connect(&homeLt, SIGNAL(clicked()), this, SLOT(getHomeLt()));
    connect(&awayLt, SIGNAL(clicked()), this, SLOT(getAwayLt()));
    connect(&homeSB, SIGNAL(clicked()), this, SLOT(getHomeSb()));
    connect(&awaySB, SIGNAL(clicked()), this, SLOT(getAwaySb()));
    connect(&awaySeason, SIGNAL(clicked(bool)), this, SLOT(getAwaySeason()));
    connect(&homeSeason, SIGNAL(clicked(bool)), this, SLOT(getHomeSeason()));

    connect(this, SIGNAL(requestAwayLt(int, bool)), game, SLOT(gatherGameStatsLt(int, bool)));
    connect(this, SIGNAL(requestHomeLt(int, bool)), game, SLOT(gatherGameStatsLt(int, bool)));
    connect(this, SIGNAL(requestAwaySb(int, bool)), game, SLOT(gatherGameStatsSb(int, bool)));
    connect(this, SIGNAL(requestHomeSb(int, bool)), game, SLOT(gatherGameStatsSb(int, bool)));
    connect(this, SIGNAL(requestAwaySeason(int,bool)), game, SLOT(gatherSeasonStatsLt(int,bool)));
    connect(this, SIGNAL(requestHomeSeason(int,bool)), game, SLOT(gatherSeasonStatsLt(int,bool)));

    connect(game->getHomeTeam(), SIGNAL(rosterChanged()), this, SLOT(updateHomeRoster()));
    connect(game->getAwayTeam(), SIGNAL(rosterChanged()), this, SLOT(updateAwayRoster()));

    emit awayGoalie.currentIndexChanged(0);
    emit homeGoalie.currentIndexChanged(0);

}

void Goalies::getHomeLt()
{
    emit requestHomeLt(homeGoalie.currentIndex(), true);
}

void Goalies::getAwayLt()
{
    emit requestAwayLt(awayGoalie.currentIndex(), false);
}

void Goalies::getHomeSb()
{
    emit requestHomeSb(homeGoalie.currentIndex(), true);
}

void Goalies::getAwaySb()
{
    emit requestAwaySb(awayGoalie.currentIndex(), false);
}

void Goalies::getAwaySeason()
{
    emit requestAwaySeason(awayGoalie.currentIndex(), false);
}

void Goalies::getHomeSeason()
{
    emit requestHomeSeason(homeGoalie.currentIndex(), true);
}

void Goalies::updateAwayRoster()
{
    disconnect(&awayGoalie, SIGNAL(currentIndexChanged(int)),
            game->getAwayTeam(), SLOT(setGoalie(int)));
    awayGoalie.clear();
    connect(&awayGoalie, SIGNAL(currentIndexChanged(int)),
                game->getAwayTeam(), SLOT(setGoalie(int)));
    awayGoalie.addItems(game->getAwayTeam()->getGuiNames());
    awayGoalie.addItem("EMPTY NET");
}

void Goalies::updateHomeRoster()
{
    disconnect(&homeGoalie, SIGNAL(currentIndexChanged(int)),
            game->getHomeTeam(), SLOT(setGoalie(int)));
    homeGoalie.clear();
    connect(&homeGoalie, SIGNAL(currentIndexChanged(int)),
            game->getHomeTeam(), SLOT(setGoalie(int)));
    homeGoalie.addItems(game->getHomeTeam()->getGuiNames());
    homeGoalie.addItem("EMPTY NET");
}
