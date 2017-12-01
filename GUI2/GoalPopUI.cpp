#include "GoalPopUI.h"
#include <QVBoxLayout>

GoalPopUI::GoalPopUI(HockeyGame *game, bool homeTeam) :
   GoalDisplayWidget(game, homeTeam, false)
{
    this->game = game;
    this->homeTeam = homeTeam;
    QVBoxLayout* myLayout = new QVBoxLayout();
    myLayout->addWidget(&previewText);
    myLayout->addLayout(createLayout());

    previewText.setText("Preview text");
    setLayout(myLayout);

    connect(&scorer, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePreview()));
    connect(&assist1, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePreview()));
    connect(&assist2, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePreview()));

    updatePreview();
    connect(team, SIGNAL(rosterChanged()), this, SLOT(updateRoster()));
}

void GoalPopUI::updatePreview()
{
    previewText.setText(game->getGoalText(scorer.currentIndex(),
                                          assist1.currentIndex(),
                                          assist2.currentIndex(),
                                          homeTeam));
}

void GoalPopUI::updateRoster()
{
    disconnect(&scorer, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePreview()));
    disconnect(&assist1, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePreview()));
    disconnect(&assist2, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePreview()));
    GoalDisplayWidget::updateRoster();
    connect(&scorer, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePreview()));
    connect(&assist1, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePreview()));
    connect(&assist2, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePreview()));
    updatePreview();
}
