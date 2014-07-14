#include "ScoreControl.h"
#include <QGridLayout>

ScoreControl::ScoreControl(HockeyGame* game) {
    QGridLayout* main = new QGridLayout();
    title.setText("Score Controls");
    main->addWidget(&title, 0, 0);
    ag.setText(game->getAwayName() + " +");
    hg.setText(game->getHomeName() + " +");
    am.setText(game->getAwayName() + " -");
    hm.setText(game->getHomeName() + " -");
    main->addWidget(&ag, 1, 0);
    main->addWidget(&hg, 1, 1);
    main->addWidget(&am, 2, 0);
    main->addWidget(&hm, 2, 1);
    main->setHorizontalSpacing(3);
    main->setVerticalSpacing(0);
    setLayout(main);

    connect(&ag, SIGNAL(clicked()), game, SLOT(awayGoal()));
    connect(&am, SIGNAL(clicked()), game, SLOT(awayLoseGoal()));
    connect(&hg, SIGNAL(clicked()), game, SLOT(homeGoal()));
    connect(&hm, SIGNAL(clicked()), game, SLOT(homeLoseGoal()));

}
