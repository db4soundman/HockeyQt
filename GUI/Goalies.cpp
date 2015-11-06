#include "Goalies.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

Goalies::Goalies(HockeyGame* game) {
    QHBoxLayout* main = new QHBoxLayout();
    QVBoxLayout* away = new QVBoxLayout();
    away->addWidget(new QLabel(game->getAwayTri()));
    awayGoalie.addItems(game->getAwayTeam()->getGuiNames());
    awayGoalie.addItem("EMPTY NET");
    away->addWidget(&awayGoalie);
    awayLt.setText("Game Lower Third");
    awaySB.setText("Game Stat Bar");
    away->addWidget(&awayLt);
    away->addWidget(&awaySB);

    QVBoxLayout* home = new QVBoxLayout();
    home->addWidget(new QLabel(game->getHomeTri()));
    homeGoalie.addItems(game->getHomeTeam()->getGuiNames());
    homeGoalie.addItem("EMPTY NET");
    home->addWidget(&homeGoalie);
    homeLt.setText("Game Lower Third");
    homeSB.setText("Game Stat Bar");
    home->addWidget(&homeLt);
    home->addWidget(&homeSB);

    main->addLayout(away);
    main->addLayout(home);

    setLayout(main);

    connect(&awayGoalie, SIGNAL(currentIndexChanged(int)),
            game->getAwayTeam(), SLOT(setGoalie(int)));
    connect(&homeGoalie, SIGNAL(currentIndexChanged(int)),
            game->getHomeTeam(), SLOT(setGoalie(int)));
    connect(&homeLt, SIGNAL(clicked()), this, SLOT(getHomeLt()));
    connect(&awayLt, SIGNAL(clicked()), this, SLOT(getAwayLt()));
    connect(&homeSB, SIGNAL(clicked()), this, SLOT(getHomeSb()));
    connect(&awaySB, SIGNAL(clicked()), this, SLOT(getAwaySb()));

    connect(this, SIGNAL(requestAwayLt(int, bool)), game, SLOT(gatherGameStatsLt(int, bool)));
    connect(this, SIGNAL(requestHomeLt(int, bool)), game, SLOT(gatherGameStatsLt(int, bool)));
    connect(this, SIGNAL(requestAwaySb(int, bool)), game, SLOT(gatherGameStatsSb(int, bool)));
    connect(this, SIGNAL(requestHomeSb(int, bool)), game, SLOT(gatherGameStatsSb(int, bool)));

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
