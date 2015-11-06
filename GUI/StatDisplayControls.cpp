#include "StatDisplayControls.h"

StatDisplayControls::StatDisplayControls(HockeyGame* game) :
    awayGoal(game, false), homeGoal(game, true), homeStats(game, true),
    awayStats(game, false), homePenalty(game, true), awayPenalty(game, false),
    goalies(game) {
    addTab(&goalies, "Goalies");
    addTab(&awayStats, game->getAwayTri() + " Stats");
    addTab(&awayGoal, game->getAwayTri()+ " Goal");
    addTab(&awayPenalty, game->getAwayTri() + " Penalty");
    addTab(&homeStats, game->getHomeTri() + " Stats");
    addTab(&homeGoal, game->getHomeTri() + " Goal");
    addTab(&homePenalty, game->getHomeTri() + " Penalty");


}
