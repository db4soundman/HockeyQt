#ifndef CLOCKCONTROLS_H
#define CLOCKCONTROLS_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "HockeyGame.h"
#include "CommercialGraphic.h"

class ClockControls : public QWidget {
    Q_OBJECT
public:
    ClockControls(HockeyGame* game, CommercialGraphic* comGraphic);

public slots:
    void updateClockButton(bool clockIsRunning);
    void showClockDialog();

private:
    QLabel label;
    QPushButton run, reset, set, nextPd, prevPd, clock, intermission, final, penalty;
    Clock* gameClock;
};

#endif // CLOCKCONTROLS_H
