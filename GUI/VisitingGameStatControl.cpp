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

    connect(this, SIGNAL(requestLt(int)), game, SLOT(gatherStatsLt(int,bool)));
    connect(this, SIGNAL(requestSb(int)), game, SLOT(gatherGameStatsSb(int,bool)));

    setLayout(main);
}

void VisitingGameStatControl::requestLt()
{
    emit requestLt(playerSelector.currentIndex(), false);
}

void VisitingGameStatControl::requestSb()
{
    emit requestSb(playerSelector.currentIndex(), false);
}
