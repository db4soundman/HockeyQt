#include "HomeStatControl.h"
#include <QHBoxLayout>

HomeStatControl::HomeStatControl(HockeyGame* game) {
    playerSelector.addItems(game->getHomeTeam()->getGuiNames());
    seasonLt.setText("Season Lower Third");
    gameLt.setText("Game Lower Third");
    seasonBar.setText("Season Stat Bar");
    gameBar.setText("Game Stat Bar");

    QHBoxLayout* main = new QHBoxLayout();
    main->addWidget(&playerSelector);
    main->addWidget(&seasonLt);
    main->addWidget(&seasonBar);
    main->addWidget(&gameLt);
    main->addWidget(&gameBar);

    connect(&seasonLt, SIGNAL(clicked()), this, SLOT(requestSeasonLt()));
    connect(this, SIGNAL(requestSeasonLt(int)), game, SLOT(gatherHomeSeasonStatsLt(int)));

    connect(&gameLt, SIGNAL(clicked()), this, SLOT(requestGameLt()));
    connect(this, SIGNAL(requestGameLt(int)), game, SLOT(gatherHomeGameStatsLt(int)));

    connect(&seasonBar, SIGNAL(clicked()), this, SLOT(requestSeasonSb()));
    connect(this, SIGNAL(requestSeasonSb(int)), game, SLOT(gatherHomeSeasonStatsSb(int)));

    connect(&gameBar, SIGNAL(clicked()), this, SLOT(requestGameSb()));
    connect(this, SIGNAL(requestGameSb(int)), game, SLOT(gatherHomeGameStatsSb(int)));

    setLayout(main);
}

void HomeStatControl::requestSeasonLt()
{
    emit requestSeasonLt(playerSelector.currentIndex());
}

void HomeStatControl::requestGameLt()
{
    emit requestGameLt(playerSelector.currentIndex());
}

void HomeStatControl::requestGameSb()
{
    emit requestGameSb(playerSelector.currentIndex());
}

void HomeStatControl::requestSeasonSb()
{
    emit requestSeasonSb(playerSelector.currentIndex());
}
