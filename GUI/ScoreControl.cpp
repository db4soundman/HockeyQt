#include "ScoreControl.h"
#include <QGridLayout>

ScoreControl::ScoreControl(HockeyGame* game) {
    QGridLayout* myLayout = new QGridLayout();
    setTitle("Score Controls");
    ag.setText(game->getAwayTri() + " +");
    hg.setText(game->getHomeTri() + " +");
    am.setText(game->getAwayTri() + " -");
    hm.setText(game->getHomeTri() + " -");
    myLayout->addWidget(&ag, 1, 0);
    myLayout->addWidget(&hg, 1, 1);
    myLayout->addWidget(&am, 2, 0);
    myLayout->addWidget(&hm, 2, 1);
    myLayout->setHorizontalSpacing(3);
    myLayout->setVerticalSpacing(0);
    setLayout(myLayout);

    connect(&ag, SIGNAL(clicked()), game, SLOT(awayGoal()));
    connect(&am, SIGNAL(clicked()), game, SLOT(awayLoseGoal()));
    connect(&hg, SIGNAL(clicked()), game, SLOT(homeGoal()));
    connect(&hm, SIGNAL(clicked()), game, SLOT(homeLoseGoal()));

    connect(game, SIGNAL(usingAllSport()), this, SLOT(disableControls()));
    connect(game, SIGNAL(usingInternalClock()), this, SLOT(enableControls()));

}

void ScoreControl::disableControls()
{
    ag.setEnabled(false);
    am.setEnabled(false);
    hg.setEnabled(false);
    hm.setEnabled(false);
}

void ScoreControl::enableControls()
{
    ag.setEnabled(true);
    am.setEnabled(true);
    hg.setEnabled(true);
    hm.setEnabled(true);
}
