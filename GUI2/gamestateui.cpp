#include "gamestateui.h"
#include <QFormLayout>
#include <QVBoxLayout>
GameStateUI::GameStateUI(HockeyGame* game):goalieUi(game)
{
    this->game = game;
    QVBoxLayout* masterLayout = new QVBoxLayout();
    QFormLayout* myLayout = new QFormLayout();
    myLayout->addRow("Time", &time);
    myLayout->addRow("Away Score", &awayScore);
    myLayout->addRow("Home Score", &homeScore);
    myLayout->addRow("Away TOL", &awayTol);
    myLayout->addRow("Home TOL", &homeTol);
    myLayout->addRow("Away Ply 1", &awayP1);
    myLayout->addRow("Away Pen 1", &awayClock1);
    myLayout->addRow("Away Ply 2", &awayP2);
    myLayout->addRow("Away Pen 2", &awayClock2);
    myLayout->addRow("Home Ply 1", &homeP1);
    myLayout->addRow("Home Pen 1", &homeClock1);
    myLayout->addRow("Home Ply 2", &homeP2);
    myLayout->addRow("Home Pen 2", &homeClock2);

    masterLayout->addLayout(myLayout);
    masterLayout->addWidget(&goalieUi);

    setLayout(masterLayout);

}

GameStateUI::~GameStateUI()
{

}

void GameStateUI::updateData()
{

}

