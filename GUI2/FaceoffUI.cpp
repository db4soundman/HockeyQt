#include "FaceoffUI.h"

FaceoffUI::FaceoffUI(HockeyGame* game):
    FaceoffControl(game, false), previewPixmap(1,1)
{
    this->game=game;
    connect(&homeFaceoffWins, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
    connect(&awayFaceoffWins, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));

    QVBoxLayout* myLayout = new QVBoxLayout();
    myLayout->addLayout(getLayout());
    myLayout->addWidget(&preview);
    setLayout(myLayout);
    updatePreview();
}

void FaceoffUI::updatePreview()
{
    previewPixmap = game->getFaceoffCompPreview(awayFaceoffWins.value(), homeFaceoffWins.value());
    preview.setPixmap(previewPixmap);
}
