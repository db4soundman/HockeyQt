#include "HomeStatControl.h"
#include <QHBoxLayout>



HomeStatControl::HomeStatControl(HockeyGame* game, bool phome, bool standAlone) : home(phome) {
    team = home ? game->getHomeTeam() : game->getAwayTeam();
    playerSelector.addItems( home ? game->getHomeTeam()->getGuiNames() :
                                    game->getAwayTeam()->getGuiNames());
    seasonLt.setText("Season Lower Third");
    gameLt.setText("Game Lower Third");
    seasonBar.setText("Season Stat Bar");
    gameBar.setText("Game Stat Bar");

    QHBoxLayout* myLayout = getFullLayout();

    connect(&seasonLt, SIGNAL(clicked()), this, SLOT(requestSeasonLt()));
    connect(this, SIGNAL(requestSeasonLt(int, bool)), game, SLOT(gatherSeasonStatsLt(int, bool)));

    connect(&gameLt, SIGNAL(clicked()), this, SLOT(requestGameLt()));
    connect(this, SIGNAL(requestGameLt(int, bool)), game, SLOT(gatherGameStatsLt(int, bool)));

    connect(&seasonBar, SIGNAL(clicked()), this, SLOT(requestSeasonSb()));
    connect(this, SIGNAL(requestSeasonSb(int, bool)), game, SLOT(gatherSeasonStatsSb(int, bool)));

    connect(&gameBar, SIGNAL(clicked()), this, SLOT(requestGameSb()));
    connect(this, SIGNAL(requestGameSb(int, bool)), game, SLOT(gatherGameStatsSb(int, bool)));
    if (standAlone) {
        connect(team, SIGNAL(rosterChanged()), this, SLOT(updateRoster()));
        setLayout(getFullLayout());
    }
}

QHBoxLayout * HomeStatControl::getFullLayout()
{
    QHBoxLayout* myLayout = new QHBoxLayout();
    myLayout->addWidget(&playerSelector);
    myLayout->addWidget(&seasonLt);
    myLayout->addWidget(&seasonBar);
    myLayout->addWidget(&gameLt);
    myLayout->addWidget(&gameBar);

    return myLayout;
}

QHBoxLayout *HomeStatControl::getPopLayout()
{
    QHBoxLayout* myLayout = new QHBoxLayout();
    myLayout->addWidget(&playerSelector);
    myLayout->addWidget(&seasonBar);
    myLayout->addWidget(&gameBar);

    return myLayout;
}

QHBoxLayout *HomeStatControl::getLowerThirdLayout()
{
    QHBoxLayout* myLayout = new QHBoxLayout();
    myLayout->addWidget(&playerSelector);
    myLayout->addWidget(&seasonLt);
    myLayout->addWidget(&gameLt);

    return myLayout;
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

void HomeStatControl::updateRoster()
{
    playerSelector.clear();
    playerSelector.addItems(team->getGuiNames());
}
