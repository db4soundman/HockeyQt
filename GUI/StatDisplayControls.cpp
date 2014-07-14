#include "StatDisplayControls.h"

StatDisplayControls::StatDisplayControls(HockeyGame* game) :
    awayGoal(game, false), homeGoal(game, true), homeStats(game),
    awayStats(game), homePenalty(game, true), awayPenalty(game, false),
    goalies(game) {
    addTab(&goalies, "Goalies");
    addTab(&awayStats, game->getAwayName() + " Game Stats");
    addTab(&awayGoal, game->getAwayName()+ " Goal");
    addTab(&awayPenalty, game->getAwayName() + " Penalty");
    addTab(&homeStats, game->getHomeName() + " Stats");
    addTab(&homeGoal, game->getHomeName() + " Goal");
    addTab(&homePenalty, game->getHomeName() + " Penalty");


}
