#include "SeasonLtUI.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>

SeasonLtUI::SeasonLtUI(HockeyGame *game, bool home):
    HomeStatControl(game, home, false)
{
    this->game = game;
    QVBoxLayout* myLayout = new QVBoxLayout();

  //  QFormLayout* playerLayout = new QFormLayout();
//playerLayout->addRow("Player", &playerSelector);
    //myLayout->addLayout(playerLayout);
    myLayout->addWidget(&playerSelector);

    QHBoxLayout* seasonRow= new QHBoxLayout();
    QHBoxLayout* gameRow= new QHBoxLayout();


    connect(&playerSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePreview()));


    seasonRow->addWidget(&seasonPreview);
    seasonRow->addWidget(&seasonLt);
    myLayout->addLayout(seasonRow);


    gameRow->addWidget(&gamePreview);
    gameRow->addWidget(&gameLt);
    myLayout->addLayout(gameRow);
    setLayout(myLayout);

    updatePreview();

}

void SeasonLtUI::updatePreview()
{
    int pIndex = playerSelector.currentIndex();
    seasonPixmap = game->getSeasonPreviewLt(pIndex, home);
    gamePixmap = game->getGamePreviewLt(pIndex, home);

    seasonPreview.setPixmap(seasonPixmap.scaled(game->getLt()->getWidth()/2,game->getLt()->getHeight()/2));
    gamePreview.setPixmap(gamePixmap.scaled(game->getLt()->getWidth()/2,game->getLt()->getHeight()/2));
}
