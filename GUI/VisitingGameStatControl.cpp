#include "VisitingGameStatControl.h"
#include <QHBoxLayout>

VisitingGameStatControl::VisitingGameStatControl(HockeyGame* game) {
    playerSelector.addItems(game->getAwayTeam()->getGuiNames());
    displayLt.setText("Show as Lower Third");
    displayBar.setText("Show on Stat Bar");

    QHBoxLayout* main = new QHBoxLayout();
    main->addWidget(&playerSelector);
    main->addWidget(&displayLt);
    main->addWidget(&displayBar);

    connect(&displayLt, SIGNAL(clicked()), this, SLOT(requestLt()));
    connect(&displayBar, SIGNAL(clicked()), this, SLOT(requestSb()));

    connect(this, SIGNAL(requestLt(int)), game, SLOT(gatherAwayStatsLt(int)));
    connect(this, SIGNAL(requestSb(int)), game, SLOT(gatherAwayGameStatsSb(int)));

    setLayout(main);
}

void VisitingGameStatControl::requestLt()
{
    emit requestLt(playerSelector.currentIndex());
}

void VisitingGameStatControl::requestSb()
{
    emit requestSb(playerSelector.currentIndex());
}
