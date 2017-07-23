#include "FaceoffControl.h"



FaceoffControl::FaceoffControl(HockeyGame *game, bool standAlone, QWidget *parent) : QWidget(parent)
{
    awayFaceoffWins.setMinimum(0);
    homeFaceoffWins.setMinimum(0);
    homeLabel.setText(game->getHomeTri());
    awayLabel.setText(game->getAwayTri());
    show.setText("Show Comparison");

    if (standAlone) setLayout(getLayout());

    connect(&show, SIGNAL(clicked(bool)), this, SLOT(requestGraphic()));
    connect(this, SIGNAL(showFaceoffComp(int,int)), game, SLOT(prepareFaceoffComparison(int,int)));
}

QGridLayout * FaceoffControl::getLayout()
{
    QGridLayout* widgetLayout = new QGridLayout();
    widgetLayout->addWidget(&awayLabel,0,0);
    widgetLayout->addWidget(&homeLabel,0,1);
    widgetLayout->addWidget(&awayFaceoffWins,1,0);
    widgetLayout->addWidget(&homeFaceoffWins,1,1);
    widgetLayout->addWidget(&show, 2, 0);

    return widgetLayout;
}
void FaceoffControl::requestGraphic()
{
    emit showFaceoffComp(awayFaceoffWins.value(), homeFaceoffWins.value());
}
