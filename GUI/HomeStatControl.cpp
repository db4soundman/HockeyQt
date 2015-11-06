#include "HomeStatControl.h"
#include <QHBoxLayout>

HomeStatControl::HomeStatControl(HockeyGame* game, bool phome) : home(phome) {
    playerSelector.addItems( home ? game->getHomeTeam()->getGuiNames() :
                                    game->getAwayTeam()->getGuiNames());
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
    connect(this, SIGNAL(requestSeasonLt(int, bool)), game, SLOT(gatherSeasonStatsLt(int, bool)));

    connect(&gameLt, SIGNAL(clicked()), this, SLOT(requestGameLt()));
    connect(this, SIGNAL(requestGameLt(int, bool)), game, SLOT(gatherGameStatsLt(int, bool)));

    connect(&seasonBar, SIGNAL(clicked()), this, SLOT(requestSeasonSb()));
    connect(this, SIGNAL(requestSeasonSb(int, bool)), game, SLOT(gatherSeasonStatsSb(int, bool)));

    connect(&gameBar, SIGNAL(clicked()), this, SLOT(requestGameSb()));
    connect(this, SIGNAL(requestGameSb(int, bool)), game, SLOT(gatherGameStatsSb(int, bool)));

    setLayout(main);
}

void HomeStatControl::requestSeasonLt()
{
    emit requestSeasonLt(playerSelector.currentIndex(), home);
}

void HomeStatControl::requestGameLt()
{
    emit requestGameLt(playerSelector.currentIndex(), home);
}

void HomeStatControl::requestGameSb()
{
    emit requestGameSb(playerSelector.currentIndex(), home);
}

void HomeStatControl::requestSeasonSb()
{
    emit requestSeasonSb(playerSelector.currentIndex(), home);
}
