#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include "HockeyGame.h"
#include "DisplayControls.h"
#include "PowerPlayUpdaters.h"
#include "PenaltyControl.h"
#include "SogControl.h"
#include "ScoreControl.h"
#include "GameInfo.h"
#include "ClockControls.h"
#include "StatDisplayControls.h"
#include "StandingsGraphic.h"
#include "CommercialGraphic.h"
#include "NchcScoreboardGraphic.h"
#include "schedulegraphic.h"


class ControlPanel : public QWidget {
    Q_OBJECT
public:
    ControlPanel(HockeyGame* game, StandingsGraphic* graphic, CommercialGraphic* comGraphic, NchcScoreboardGraphic* sbGraphic, ScheduleGraphic* schedGraphic);

private:
    DisplayControls dispControls;
    PowerPlayUpdaters ppus;
    PenaltyControl penaltyControl;
    SogControl sogs;
    ScoreControl scores;
    GameInfo hud;
    ClockControls clockControls;
    StatDisplayControls stats;
};

#endif // CONTROLPANEL_H
