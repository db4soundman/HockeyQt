#ifndef TEAMEDITOR_H
#define TEAMEDITOR_H

#include <QWidget>
#include <QSpinBox>
#include "HockeyTeam.h"

class TeamEditor : public QWidget {
    Q_OBJECT
public:
    TeamEditor(HockeyTeam* pTeam);

public slots:
    void updateSpinBoxes();
    void changeStats();

private:
    HockeyTeam* team;
    QSpinBox ppg, ppopp, pk, pkopp;
    int ppgS, ppoppS, pkS, pkoppS;

};

#endif // TEAMEDITOR_H
