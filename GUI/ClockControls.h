#ifndef CLOCKCONTROLS_H
#define CLOCKCONTROLS_H

#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include "HockeyGame.h"
#include "CommercialGraphic.h"
#include "CheckboxWidget.h"

class ClockControls : public QGroupBox {
    Q_OBJECT
public:
    ClockControls(HockeyGame* game, CommercialGraphic* comGraphic, bool dakMode=false);

public slots:
    void updateClockButton(bool clockIsRunning);
    void showClockDialog();
    void disableClockControls();
    void enableClockControls();
    void switchShowText();

    void handleAutomatedIntermission();
    void handleAutomatedFinal();
    void handleAutomatedNewPeriod();

private:
    //QLabel label;
    QPushButton run, reset, set, nextPd, prevPd, clock, intermission, final, penalty, showPenalties;
    QCheckBox useClock;
    Clock* gameClock;
    CheckBoxWidget statCrewControl;
    QLineEdit statCrewUrl;
};

#endif // CLOCKCONTROLS_H
