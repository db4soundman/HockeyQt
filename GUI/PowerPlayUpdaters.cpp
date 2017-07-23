#include "PowerPlayUpdaters.h"
#include <QGridLayout>

PowerPlayUpdaters::PowerPlayUpdaters(HockeyGame* game) {
    QGridLayout* myLayout = new QGridLayout();
    awayLabel.setText(game->getAwayTri() + " Power Play");
    homeLabel.setText(game->getHomeTri() + " Power Play");
    awayGoal.setText("GOAL");
    awayFail.setText("FAIL");
    homeGoal.setText("GOAL");
    homeFail.setText("FAIL");
    show.setText("Show Comparison");

    myLayout->addWidget(&awayLabel, 0, 0);
    myLayout->addWidget(&homeLabel, 0, 1);
    myLayout->addWidget(&awayGoal, 1, 0);
    myLayout->addWidget(&homeGoal, 1, 1);
    myLayout->addWidget(&awayFail, 2, 0);
    myLayout->addWidget(&homeFail, 2, 1);
    myLayout->addWidget(&show, 3,0,1,2);

    connect(&awayGoal, SIGNAL(clicked()), game->getAwayTeam(), SLOT(addPpg()));
    connect(&awayGoal, SIGNAL(clicked()), game->getHomeTeam(), SLOT(addPkFail()));
    connect(&awayFail, SIGNAL(clicked()), game->getAwayTeam(), SLOT(addPpFail()));
    connect(&awayFail, SIGNAL(clicked()), game->getHomeTeam(), SLOT(addPkStop()));

    connect(&homeGoal, SIGNAL(clicked()), game->getHomeTeam(), SLOT(addPpg()));
    connect(&homeGoal, SIGNAL(clicked()), game->getAwayTeam(), SLOT(addPkFail()));
    connect(&homeFail, SIGNAL(clicked()), game->getHomeTeam(), SLOT(addPpFail()));
    connect(&homeFail, SIGNAL(clicked()), game->getAwayTeam(), SLOT(addPkStop()));

    connect(&show, SIGNAL(clicked()), game, SLOT(gatherPpStats()));

    myLayout->setHorizontalSpacing(3);
    myLayout->setVerticalSpacing(0);
    setLayout(myLayout);
}
