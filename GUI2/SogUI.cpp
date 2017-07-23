#include "SogUI.h"
#include <QVBoxLayout>
SogUI::SogUI(HockeyGame *game):
    SogControl(game, false), previewPixmap(1,1)
{
    this->game=game;
    connect(game, SIGNAL(awaySogChanged(int)), this, SLOT(updatePreview()));
    connect(game, SIGNAL(homeSogChanged(int)), this, SLOT(updatePreview()));

    QVBoxLayout* myLayout = new QVBoxLayout();
    myLayout->addLayout(getLayout());
    myLayout->addWidget(&compPreview);
    setLayout(myLayout);
    updatePreview();
}

void SogUI::updatePreview()
{
    previewPixmap = game->getSogComparisonPreview();
    compPreview.setPixmap(previewPixmap);
}
