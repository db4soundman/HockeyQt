#include "ClockControls.h"
#include <QVBoxLayout>
#include "ClockDialog.h"

ClockControls::ClockControls(HockeyGame* game) {
    QVBoxLayout* main = new QVBoxLayout();
    label.setText("Clock Controls");
    run.setText("Run Clock");
    set.setText("Set Clock");
    reset.setText("Reset Clock");
    nextPd.setText("Next Period");
    prevPd.setText("Previous Period");
    clock.setText("Clock");
    intermission.setText("INT");
    final.setText("FINAL");
    penalty.setText("Penalty");

    main->addWidget(&label);
    main->addWidget(&run);
    main->addWidget(&set);
    main->addWidget(&penalty);
    main->addWidget(&nextPd);
    main->addWidget(&prevPd);
    main->addWidget(&reset);
    main->addWidget(&clock);
    main->addWidget(&intermission);
    main->addWidget(&final);

    connect(&run, SIGNAL(clicked()), game, SLOT(toggleClock()));
    connect(game, SIGNAL(clockIsRunning(bool)),
            this, SLOT(updateClockButton(bool)));
    connect(&set, SIGNAL(clicked()), this, SLOT(showClockDialog()));
    connect(&penalty, SIGNAL(clicked()), game->getSb(), SLOT(togglePenalty()));
    connect(&nextPd, SIGNAL(clicked()), game, SLOT(advancePeriod()));
    connect(&prevPd, SIGNAL(clicked()), game, SLOT(rewindPeriod()));
    connect(&reset, SIGNAL(clicked()), game->getGameClock(), SLOT(resetClock()));
    connect(&clock, SIGNAL(clicked()), game->getSb(), SLOT(displayClock()));
    connect(&intermission, SIGNAL(clicked()), game->getSb(), SLOT(intermission()));
    connect(&final, SIGNAL(clicked()), game->getSb(), SLOT(final()));
    setLayout(main);

    gameClock = game->getGameClock();
}

void ClockControls::updateClockButton(bool clockIsRunning) {
    run.setText( clockIsRunning ? "Stop Clock" : "Run Clock");
}

void ClockControls::showClockDialog()
{
    ClockDialog cd(gameClock);
    cd.exec();
}
