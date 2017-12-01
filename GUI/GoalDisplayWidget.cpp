#include "GoalDisplayWidget.h"


GoalDisplayWidget::GoalDisplayWidget(HockeyGame* game, bool homeTeam, bool standAlone) {
    team = homeTeam ? game->getHomeTeam() : game->getAwayTeam();
    scorer.addItems( homeTeam ? game->getHomeTeam()->getGuiNames() :
                                game->getAwayTeam()->getGuiNames());
    assist1.addItems( homeTeam ? game->getHomeTeam()->getGuiNames() :
                                 game->getAwayTeam()->getGuiNames());
    assist2.addItems( homeTeam ? game->getHomeTeam()->getGuiNames() :
                                 game->getAwayTeam()->getGuiNames());
    show.setText("Display Goal Info");

    shooter.setText("Goal Scorer:");
    firstAssister.setText("Assist 1:");
    secondAssister.setText("Assist 2:");
    assist1.addItem("UNASSISTED");
    assist2.addItem("UNASSISTED");

    if (standAlone) {
        setLayout(createLayout());
    }


    connect(&show, SIGNAL(clicked()), this, SLOT(prepareToSendSignal()));
    if (homeTeam)
        connect(this, SIGNAL(showGoalText(int,int,int)),
                game, SLOT(prepareHomeGoalText(int,int,int)));
    else
        connect(this, SIGNAL(showGoalText(int,int,int)),
                game, SLOT(prepareAwayGoalText(int,int,int)));
    if (standAlone)
        connect(team, SIGNAL(rosterChanged()), this, SLOT(updateRoster()));
}

QGridLayout* GoalDisplayWidget::createLayout()
{
    QGridLayout* myLayout = new QGridLayout();
    myLayout->addWidget(&shooter, 0, 0);
    myLayout->addWidget(&firstAssister,0,1);
    myLayout->addWidget(&secondAssister,0,2);
    myLayout->addWidget(&scorer, 1,0);
    myLayout->addWidget(&assist1, 1,1);
    myLayout->addWidget(&assist2, 1, 2);
    myLayout->addWidget(&show, 2, 0, 1, 3);
    return myLayout;
}

void GoalDisplayWidget::prepareToSendSignal()
{
    emit showGoalText(scorer.currentIndex(), assist1.currentIndex(), assist2.currentIndex());
}

void GoalDisplayWidget::updateRoster()
{
    scorer.clear();
    assist1.clear();
    assist2.clear();
    scorer.addItems(team->getGuiNames());
    assist1.addItems(team->getGuiNames());
    assist2.addItems(team->getGuiNames());
    assist1.addItem("UNASSISTED");
    assist2.addItem("UNASSISTED");
}
