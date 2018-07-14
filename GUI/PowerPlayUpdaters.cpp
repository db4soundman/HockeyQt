#include "PowerPlayUpdaters.h"
#include "MiamiAllAccessHockey.h"
PowerPlayUpdaters::PowerPlayUpdaters(HockeyGame* game, bool standAlone) {
    awayLabel.setText(MiamiAllAccessHockey::awaySchool.getShortName() + " Power Play");
    homeLabel.setText(MiamiAllAccessHockey::homeSchool.getShortName() + " Power Play");
    awayGoal.setText("GOAL");
    awayFail.setText("FAIL");
    homeGoal.setText("GOAL");
    homeFail.setText("FAIL");
    show.setText("Show Comparison");

    connect(&awayGoal, SIGNAL(clicked()), game->getAwayTeam(), SLOT(addPpg()));
    connect(&awayGoal, SIGNAL(clicked()), game->getHomeTeam(), SLOT(addPkFail()));
    connect(&awayFail, SIGNAL(clicked()), game->getAwayTeam(), SLOT(addPpFail()));
    connect(&awayFail, SIGNAL(clicked()), game->getHomeTeam(), SLOT(addPkStop()));

    connect(&homeGoal, SIGNAL(clicked()), game->getHomeTeam(), SLOT(addPpg()));
    connect(&homeGoal, SIGNAL(clicked()), game->getAwayTeam(), SLOT(addPkFail()));
    connect(&homeFail, SIGNAL(clicked()), game->getHomeTeam(), SLOT(addPpFail()));
    connect(&homeFail, SIGNAL(clicked()), game->getAwayTeam(), SLOT(addPkStop()));

    connect(&show, SIGNAL(clicked()), game, SLOT(gatherPpStats()));

    if (standAlone) setLayout(getLayout());
}


QGridLayout * PowerPlayUpdaters::getLayout()
{
    QGridLayout* myLayout = new QGridLayout();
    myLayout->addWidget(&awayLabel, 0, 0);
    myLayout->addWidget(&homeLabel, 0, 1);
    myLayout->addWidget(&awayGoal, 1, 0);
    myLayout->addWidget(&homeGoal, 1, 1);
    myLayout->addWidget(&awayFail, 2, 0);
    myLayout->addWidget(&homeFail, 2, 1);
    myLayout->addWidget(&show, 3,0,1,2);
    myLayout->setHorizontalSpacing(3);
    myLayout->setVerticalSpacing(0);

    return myLayout;
}
