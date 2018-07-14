#include "StatDisplayControls.h"
#include "MiamiAllAccessHockey.h"

StatDisplayControls::StatDisplayControls(HockeyGame* game) :
    awayGoal(game, false), homeGoal(game, true), homeStats(game, true),
    awayStats(game, false), homePenalty(game, true), awayPenalty(game, false),
    goalies(game) {
    addTab(&goalies, "Goalies");
    addTab(&awayStats, MiamiAllAccessHockey::awaySchool.getShortName() + " Stats");
    addTab(&awayGoal, MiamiAllAccessHockey::awaySchool.getShortName() + " Goal");
    addTab(&awayPenalty, MiamiAllAccessHockey::awaySchool.getShortName() + " Penalty");
    addTab(&homeStats, MiamiAllAccessHockey::homeSchool.getShortName() + " Stats");
    addTab(&homeGoal, MiamiAllAccessHockey::homeSchool.getShortName() + " Goal");
    addTab(&homePenalty, MiamiAllAccessHockey::homeSchool.getShortName() + " Penalty");


}
