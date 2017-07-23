#include "ClockControls.h"
#include <QVBoxLayout>
#include "ClockDialog.h"

ClockControls::ClockControls(HockeyGame* game, CommercialGraphic* comGraphic, bool dakMode) : statCrewControl(game) {
    QVBoxLayout* myLayout = new QVBoxLayout();
    useClock.setText("Use Clock");
    useClock.setChecked(true);
    setTitle("Clock Controls");
    run.setText("Run Clock");
    set.setText("Set Clock");
    reset.setText("Reset Clock");
    nextPd.setText("Next Period");
    prevPd.setText("Previous Period");
    clock.setText("Clock");
    intermission.setText("INT");
    final.setText("FINAL");
    penalty.setText("Penalty");
   // main->addWidget(&label);
    if (!dakMode) myLayout->addWidget(&run);
    if (!dakMode)myLayout->addWidget(&set);
    myLayout->addWidget(&penalty);
    myLayout->addWidget(&nextPd);
    myLayout->addWidget(&prevPd);
    if (!dakMode) myLayout->addWidget(&reset);
    myLayout->addWidget(&clock);
    myLayout->addWidget(&intermission);
    myLayout->addWidget(&final);
    myLayout->addSpacing(50);
    myLayout->addWidget(&useClock);
    //main->addWidget(&statCrewControl);

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

    connect(game, SIGNAL(usingAllSport()), this, SLOT(disableClockControls()));
    connect(game, SIGNAL(usingInternalClock()), this, SLOT(enableClockControls()));
    setLayout(myLayout);

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

void ClockControls::disableClockControls()
{
    run.setEnabled(false);
    set.setEnabled(false);
    reset.setEnabled(false);

}

void ClockControls::enableClockControls()
{
    run.setEnabled(true);
    set.setEnabled(true);
    reset.setEnabled(true);
}
