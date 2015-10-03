#include "ControlPanel.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

ControlPanel::ControlPanel(HockeyGame* game, StandingsGraphic* graphic, CommercialGraphic* comGraphic, NchcScoreboardGraphic* sbGraphic) :
    dispControls(game, graphic, comGraphic, sbGraphic), ppus(game), penaltyControl(game), sogs(game),
    scores(game), hud(game), clockControls(game, comGraphic), stats(game) {
    QHBoxLayout* mainLayout = new QHBoxLayout();

    QVBoxLayout* leftColumn = new QVBoxLayout();
    leftColumn->addWidget(&dispControls);
    QGridLayout* grid = new QGridLayout();
    grid->addWidget(&ppus, 1, 0, Qt::AlignHCenter | Qt::AlignTop);
    grid->addWidget(&penaltyControl, 1, 1);
    grid->addWidget(&sogs, 0, 0,Qt::AlignHCenter | Qt::AlignTop);
    grid->addWidget(&scores, 0, 1, Qt::AlignHCenter | Qt::AlignTop );

    leftColumn->addLayout(grid);
    leftColumn->addWidget(&stats);

    QVBoxLayout* rightColumn = new QVBoxLayout();
    rightColumn->addWidget(&hud);
    rightColumn->addWidget(&clockControls);
    rightColumn->addSpacing(0);


    mainLayout->addLayout(leftColumn, 1);
    mainLayout->addLayout(rightColumn);
    setLayout(mainLayout);
}
