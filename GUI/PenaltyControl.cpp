#include "PenaltyControl.h"
#include <QGridLayout>

PenaltyControl::PenaltyControl(HockeyGame* game) {
    clockLayout = new QGridLayout();
    setTitle("Penalty Controls");
    awayLabel.setText(game->getAwayTri() + " PENALTY");
    homeLabel.setText(game->getHomeTri() + " PENALTY");
    ap2.setText("+ 2:00");
    ap4.setText("+ 4:00");
    ap5.setText("+ 5:00");
    hp2.setText("+ 2:00");
    hp4.setText("+ 4:00");
    hp5.setText("+ 5:00");
    show.setText("Show");
    set.setText("Change Timers");
    awayPenEnd.setText("Remove Penalty");
    homePenEnd.setText("Remove Penalty");

    clockLayout->addWidget(&awayLabel, 0, 0);
    clockLayout->addWidget(&homeLabel, 0, 1);
    clockLayout->addWidget(&ap2, 1, 0);
    clockLayout->addWidget(&hp2, 1,1);
    clockLayout->addWidget(&ap4, 2,0);
    clockLayout->addWidget(&hp4, 2,1);
    clockLayout->addWidget(&ap5, 3, 0);
    clockLayout->addWidget(&hp5, 3, 1);
    clockLayout->addWidget(&awayPenEnd,4,0);
    clockLayout->addWidget(&homePenEnd,4,1);
    clockLayout->addWidget(&show, 5, 0);
    clockLayout->addWidget(&set, 5, 1);
    clockLayout->setHorizontalSpacing(3);
    clockLayout->setVerticalSpacing(0);
    setLayout(clockLayout);


    connect(&ap2, SIGNAL(clicked()), this, SLOT(awayTwo()));
    connect(&ap4, SIGNAL(clicked()), this, SLOT(awayFour()));
    connect(&awayPenEnd, SIGNAL(clicked()), game, SLOT(removeFirstAwayPenalty()));
    connect(&ap5, SIGNAL(clicked()), this, SLOT(awayFive()));
    connect(&hp2, SIGNAL(clicked()), this, SLOT(homeTwo()));
    connect(&hp4, SIGNAL(clicked()), this, SLOT(homeFour()));
    connect(&homePenEnd, SIGNAL(clicked()), game, SLOT(removeFirstHomePenalty()));
    connect(&hp5, SIGNAL(clicked()), this, SLOT(homeFive()));
    connect(&show, SIGNAL(clicked()), game->getSb(), SLOT(togglePpClocks()));
    connect(&set, SIGNAL(clicked()), this, SIGNAL(editPenalties()));
    connect(this, SIGNAL(editPenalties()), game, SLOT(displayPenaltyEditor()));
    connect(this, SIGNAL(awayPenalty(int)), game, SLOT(addAwayPenalty(int)));
    connect(this, SIGNAL(homePenalty(int)), game, SLOT(addHomePenalty(int)));
    connect(game, SIGNAL(clockInUse(bool)), this, SLOT(changeUseClock(bool)));
}

void PenaltyControl::changeUseClock(bool uc)
{

    if (uc) {
        ap2.setText("+ 2:00");
        ap4.setEnabled(true);
        hp2.setText("+ 2:00");
        hp4.setEnabled(true);
        ap5.setEnabled(true);
        hp5.setEnabled(true);
        show.setEnabled(true);
        set.setEnabled(true);
    }
    else {
        ap2.setText("Penalty +");
        hp2.setText("Penalty +");
        ap4.setEnabled(false);
        hp4.setEnabled(false);
        ap5.setEnabled(false);
        hp5.setEnabled(false);
        //show.setEnabled(false);
        set.setEnabled(false);
    }
}

void PenaltyControl::awayTwo()
{
    emit awayPenalty(2);
}

void PenaltyControl::awayFour()
{
    emit awayPenalty(4);
}

void PenaltyControl::awayFive()
{
    emit awayPenalty(5);
}

void PenaltyControl::homeTwo()
{
    emit homePenalty(2);
}

void PenaltyControl::homeFour()
{
    emit homePenalty(4);
}

void PenaltyControl::homeFive()
{
    emit homePenalty(5);
}
