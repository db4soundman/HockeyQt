#include "PowerPlayUpdaters.h"
#include <QGridLayout>

PowerPlayUpdaters::PowerPlayUpdaters(HockeyGame* game) {
    QGridLayout* main = new QGridLayout();

    awayLabel.setText(game->getAwayName() + " Power Play");
    homeLabel.setText(game->getHomeName() + " Power Play");
    awayGoal.setText("GOAL");
    awayFail.setText("FAIL");
    homeGoal.setText("GOAL");
    homeFail.setText("FAIL");
    show.setText("Show Comparison");

    main->addWidget(&awayLabel, 0, 0);
    main->addWidget(&homeLabel, 0, 1);
    main->addWidget(&awayGoal, 1, 0);
    main->addWidget(&homeGoal, 1, 1);
    main->addWidget(&awayFail, 2, 0);
    main->addWidget(&homeFail, 2, 1);
    main->addWidget(&show, 3,0,1,2);

    connect(&awayGoal, SIGNAL(clicked()), game->getAwayTeam(), SLOT(addPpg()));
    connect(&awayGoal, SIGNAL(clicked()), game->getHomeTeam(), SLOT(addPkFail()));
    connect(&awayFail, SIGNAL(clicked()), game->getAwayTeam(), SLOT(addPpFail()));
    connect(&awayFail, SIGNAL(clicked()), game->getHomeTeam(), SLOT(addPkStop()));

    connect(&homeGoal, SIGNAL(clicked()), game->getHomeTeam(), SLOT(addPpg()));
    connect(&homeGoal, SIGNAL(clicked()), game->getAwayTeam(), SLOT(addPkFail()));
    connect(&homeFail, SIGNAL(clicked()), game->getHomeTeam(), SLOT(addPpFail()));
    connect(&homeFail, SIGNAL(clicked()), game->getAwayTeam(), SLOT(addPkStop()));

    connect(&show, SIGNAL(clicked()), game, SLOT(gatherPpStats()));

    main->setHorizontalSpacing(3);
    main->setVerticalSpacing(0);
    setLayout(main);
}
