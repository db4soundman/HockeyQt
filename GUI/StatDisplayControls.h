#ifndef STATDISPLAYCONTROLS_H
#define STATDISPLAYCONTROLS_H

#include <QTabWidget>
#include "HockeyGame.h"
#include "GoalDisplayWidget.h"
#include "HomeStatControl.h"
#include "VisitingGameStatControl.h"
#include "PenaltyDisplay.h"
#include "Goalies.h"

class StatDisplayControls : public QTabWidget {
    Q_OBJECT
public:
    StatDisplayControls(HockeyGame* game);

private:
    GoalDisplayWidget homeGoal, awayGoal;
    HomeStatControl homeStats, awayStats;
    //VisitingGameStatControl awayStats;
    PenaltyDisplay homePenalty, awayPenalty;
    Goalies goalies;

};

#endif // STATDISPLAYCONTROLS_H
