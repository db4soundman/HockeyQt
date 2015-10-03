#include "PenaltyControl.h"
#include <QGridLayout>

PenaltyControl::PenaltyControl(HockeyGame* game) {
    QGridLayout* main = new QGridLayout();
    awayLabel.setText(game->getAwayTri());
    homeLabel.setText(game->getHomeTri());
    ap2.setText("+ 2");
    ap4.setText("+ 4");
    ap5.setText("+ 5");
    hp2.setText("+ 2");
    hp4.setText("+ 4");
    hp5.setText("+ 5");
    show.setText("Show");
    set.setText("Change Timers");

    main->addWidget(&awayLabel, 0, 0);
    main->addWidget(&homeLabel, 0, 1);
    main->addWidget(&ap2, 1, 0);
    main->addWidget(&hp2, 1,1);
    main->addWidget(&ap4, 2,0);
    main->addWidget(&hp4, 2,1);
    main->addWidget(&ap5, 3, 0);
    main->addWidget(&hp5, 3, 1);
    main->addWidget(&show, 4, 0);
    main->addWidget(&set, 4, 1);
    main->setHorizontalSpacing(3);
    main->setVerticalSpacing(0);
    setLayout(main);


    connect(&ap2, SIGNAL(clicked()), this, SLOT(awayTwo()));
    connect(&ap4, SIGNAL(clicked()), this, SLOT(awayFour()));
    connect(&ap5, SIGNAL(clicked()), this, SLOT(awayFive()));
    connect(&hp2, SIGNAL(clicked()), this, SLOT(homeTwo()));
    connect(&hp4, SIGNAL(clicked()), this, SLOT(homeFour()));
    connect(&hp5, SIGNAL(clicked()), this, SLOT(homeFive()));
    connect(&show, SIGNAL(clicked()), game->getSb(), SLOT(togglePpClocks()));
    connect(&set, SIGNAL(clicked()), this, SIGNAL(editPenalties()));
    connect(this, SIGNAL(editPenalties()), game, SLOT(displayPenaltyEditor()));
    connect(this, SIGNAL(awayPenalty(int)), game, SLOT(addAwayPenalty(int)));
    connect(this, SIGNAL(homePenalty(int)), game, SLOT(addHomePenalty(int)));
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
