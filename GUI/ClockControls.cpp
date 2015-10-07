#include "ClockControls.h"
#include <QVBoxLayout>
#include "ClockDialog.h"

ClockControls::ClockControls(HockeyGame* game, CommercialGraphic* comGraphic) : statCrewControl(game) {
    QVBoxLayout* main = new QVBoxLayout();
    useClock.setText("Use Clock");
    useClock.setChecked(true);
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
    main->addSpacing(50);
    main->addWidget(&useClock);
    main->addWidget(&statCrewControl);

    connect(&run, SIGNAL(clicked()), game, SLOT(toggleClock()));
    connect(game, SIGNAL(clockIsRunning(bool)),
            this, SLOT(updateClockButton(bool)));
    connect(&set, SIGNAL(clicked()), this, SLOT(showClockDialog()));
    connect(&penalty, SIGNAL(clicked()), game->getSb(), SLOT(togglePenalty()));
    connect(&nextPd, SIGNAL(clicked()), game, SLOT(advancePeriod()));
    connect(&prevPd, SIGNAL(clicked()), game, SLOT(rewindPeriod()));
    connect(&reset, SIGNAL(clicked()), game->getGameClock(), SLOT(resetClock()));
    connect(&clock, SIGNAL(clicked()), game->getSb(), SLOT(displayClock()));
    connect(&clock, SIGNAL(clicked()), comGraphic, SLOT(showClock()));
    connect(&intermission, SIGNAL(clicked()), game->getSb(), SLOT(intermission()));
    connect(&intermission, SIGNAL(clicked()), comGraphic, SLOT(intermissionTime()));
    connect(&final, SIGNAL(clicked()), game->getSb(), SLOT(final()));
    connect(&final, SIGNAL(clicked()), comGraphic, SLOT(finalTime()));
    connect(&useClock, SIGNAL(toggled(bool)), game->getSb(), SLOT(changeUseClock(bool)));
    connect(&useClock, SIGNAL(toggled(bool)), game, SLOT(changeUseClock(bool)));
    connect(&useClock, SIGNAL(toggled(bool)), comGraphic, SLOT(changeUseClock(bool)));
    connect(&useClock, SIGNAL(toggled(bool)), &run, SLOT(setEnabled(bool)));
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
