#include "GoalDisplayWidget.h"
#include <QGridLayout>

GoalDisplayWidget::GoalDisplayWidget(HockeyGame* game, bool homeTeam) {
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
    QGridLayout* main = new QGridLayout();
    main->addWidget(&shooter, 0, 0);
    main->addWidget(&firstAssister,0,1);
    main->addWidget(&secondAssister,0,2);
    main->addWidget(&scorer, 1,0);
    main->addWidget(&assist1, 1,1);
    main->addWidget(&assist2, 1, 2);
    main->addWidget(&show, 2, 0, 1, 3);

    connect(&show, SIGNAL(clicked()), this, SLOT(prepareToSendSignal()));
    if (homeTeam)
        connect(this, SIGNAL(showGoalText(int,int,int)),
                game, SLOT(prepareHomeGoalText(int,int,int)));
    else
        connect(this, SIGNAL(showGoalText(int,int,int)),
                game, SLOT(prepareAwayGoalText(int,int,int)));
    setLayout(main);
}

void GoalDisplayWidget::prepareToSendSignal()
{
    emit showGoalText(scorer.currentIndex(), assist1.currentIndex(), assist2.currentIndex());
}
