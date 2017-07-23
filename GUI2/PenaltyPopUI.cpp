#include "PenaltyPopUI.h"

#include <QVBoxLayout>

PenaltyPopUI::PenaltyPopUI(HockeyGame *game, bool homeTeam):
    PenaltyDisplay(game, homeTeam, false)
{
    this->game = game;
    this->homeTeam = homeTeam;

    connect(&playerSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePreviewText()));
    connect(&penaltySelector, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePreviewText()));

    QVBoxLayout* myLayout = new QVBoxLayout();
    myLayout->addWidget(&previewText);
    myLayout->addLayout(createLayout());

    setLayout(myLayout);
    updatePreviewText();
}

void PenaltyPopUI::updatePreviewText()
{
    previewText.setText(game->getPenaltyText(playerSelector.currentIndex(),
                                             penaltySelector.currentText(),
                                             homeTeam));
}
