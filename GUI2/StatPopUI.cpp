#include "StatPopUI.h"
#include <QVBoxLayout>

StatPopUI::StatPopUI(HockeyGame *game, bool phome):
    HomeStatControl(game, phome, false)
{
    this->game=game;
    QVBoxLayout* myLayout = new QVBoxLayout();
    myLayout->addWidget(&seasonPreview);
    myLayout->addWidget(&gamePreview);
    myLayout->addLayout(getPopLayout());
    setLayout(myLayout);
    connect(&playerSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(updateGamePreview()));
    connect(&playerSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSeasonPreview()));
    HockeyTeam* team = home? game->getHomeTeam() : game->getAwayTeam();
    connect(team, SIGNAL(rosterChanged()), this, SLOT(updateRoster()));
    updateSeasonPreview();
    updateGamePreview();
}

void StatPopUI::updateSeasonPreview()
{
    seasonPreview.setText("SEASON: " + game->getSeasonPopText(playerSelector.currentIndex(),home));
}

void StatPopUI::updateGamePreview()
{
    gamePreview.setText("GAME: " + game->getGamePopText(playerSelector.currentIndex(),home));
}

void StatPopUI::updateRoster()
{
    disconnect(&playerSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(updateGamePreview()));
    disconnect(&playerSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSeasonPreview()));
    HomeStatControl::updateRoster();
    connect(&playerSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(updateGamePreview()));
    connect(&playerSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSeasonPreview()));
    updateSeasonPreview();
    updateGamePreview();
}
