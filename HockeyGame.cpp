#include "HockeyGame.h"

HockeyGame::HockeyGame(QString awayName, QString homeName) :
    awayName(awayName), homeName(homeName) {
    awayScore = 0;
    homeScore = 0;
    homeSOG = 0;
    awaySOG = 0;
    period = 0;
    timer.setInterval(100);
    clockRunning = false;

    connect(&gameClock, SIGNAL(clockExpired()),
            this, SLOT(toggleClock()));
    connect(&timer, SIGNAL(timeout()), &gameClock, SLOT(tick()));
    // Make teams...
}

void
HockeyGame::awayGoal() {
    awayScore ++;
    emit awayScoreChanged(awayScore);
}

void
HockeyGame::awayLoseGoal() {
    awayScore --;
    emit awayScoreChanged(awayScore);
}

void
HockeyGame::homeGoal() {
    homeScore ++;
    emit homeScoreChanged(homeScore);
}

void
HockeyGame::homeLoseGoal() {
    homeScore --;
    emit homeScoreChanged(homeScore);
}

void
HockeyGame::addAwaySOG() {
    awaySOG++;
    emit awaySogChanged(awaySOG);
}

void
HockeyGame::subAwaySOG() {
    awaySOG--;
    emit awaySogChanged(awaySOG);
}

void
HockeyGame::addHomeSOG() {
    homeSOG++;
    emit homeSogChanged(homeSOG);
}

void
HockeyGame::subHomeSOG() {
    homeSOG--;
    emit homeSogChanged(homeSOG);
}

void
HockeyGame::advancePeriod() {
    period++;
    emit periodChanged(period);
}

void
HockeyGame::rewindPeriod() {
    period--;
    emit periodChanged(period);
}

void
HockeyGame::addHomePenalty(int time) {
    Clock* pc = new Clock(time);
    homePenalty.append(pc);
    connect(&timer, SIGNAL(timeout()),
            pc, SLOT(tick()));
    connect(pc, SIGNAL(clockExpired()),
            this, SLOT(homePenaltyExpired()));
    determinePpClockForScoreboard();
}

void
HockeyGame::addAwayPenalty(int time) {
    Clock* pc = new Clock(time);
    awayPenalty.append(pc);
    connect(&timer, SIGNAL(timeout()),
            pc, SLOT(tick()));
    connect(pc, SIGNAL(clockExpired()),
            this, SLOT(awayPenaltyExpired()));
    determinePpClockForScoreboard();

}

void
HockeyGame::awayPenaltyExpired() {
    for (int i = 0; i < awayPenalty.size(); i++) {
        if (awayPenalty.at(i)->getTimeLeft() == 0) {
            delete awayPenalty.at(i);
            awayPenalty.removeAt(i);
        }
    }
    determinePpClockForScoreboard();
}

void
HockeyGame::homePenaltyExpired() {
    for (int i = 0; i < homePenalty.size(); i++) {
        if (homePenalty.at(i)->getTimeLeft() == 0) {
            delete homePenalty.at(i);
            homePenalty.removeAt(i);
        }
    }
    determinePpClockForScoreboard();
}

void
HockeyGame::determinePpClockForScoreboard() {
    int homePlayersOnIce, awayPlayersOnIce, ppPos;
    QString description = "";
    homePlayersOnIce = 5 - homePenalty.size();
    awayPlayersOnIce = 5 - awayPenalty.size();
    QString num;

    // Neutral
    if (homePlayersOnIce == awayPlayersOnIce && homePlayersOnIce < 5) {
        ppPos = 3;
        num.setNum(homePlayersOnIce, 10);
        description = num + "-ON-" + num;
    }
    // home pp
    else if (homePlayersOnIce > awayPlayersOnIce) {
        ppPos = 2;
        // typical pp
        if (awayPlayersOnIce == 4) {
            description = "POWERPLAY";
        }
        else {
            description = num.setNum(homePlayersOnIce, 10) + "-ON-" +
                    num.setNum(awayPlayersOnIce);
        }
    }
    // away pp
    else if (awayPlayersOnIce < homePlayersOnIce){
        ppPos = 1;
        // typical pp
        if (homePlayersOnIce == 4) {
            description = "POWERPLAY";
        }
        else {
            description = num.setNum(awayPlayersOnIce, 10) + "-ON-" +
                    num.setNum(homePlayersOnIce);
        }
    }
    else {
        ppPos = 0;
    }
    Clock* ppClock = getLowestPpClock();
    emit penaltyChanged(ppPos, ppClock, description);

}

void
HockeyGame::toggleClock() {
    clockRunning = !clockRunning;
    if (clockRunning) {
        timer.start();
    }
    else {
        timer.stop();
    }
    emit clockIsRunning(clockRunning);
}

Clock*
HockeyGame::getLowestPpClock() {
    Clock* homePP = NULL;
    Clock* awayPP = NULL;

    for (int i = 0; i < homePenalty.size(); i++) {
        if (i == 0) {
            homePP = homePenalty.at(i);
        }
        else {
            if (homePenalty.at(i)->getTimeLeft() < homePP->getTimeLeft()) {
                homePP = homePenalty.at(i);
            }
        }
    }
    for (int i = 0; i < awayPenalty.size(); i++) {
        if (i == 0) {
            awayPP = awayPenalty.at(i);
        }
        else {
            if (awayPenalty.at(i)->getTimeLeft() < awayPP->getTimeLeft()) {
                awayPP = awayPenalty.at(i);
            }
        }
    }
    if (homePP == NULL) {
        return awayPP;
    }
    if (awayPP == NULL) {
        return homePP;
    }
    if (homePP->getTimeLeft() <  awayPP->getTimeLeft()) {
        return homePP;
    }
    return awayPP;
}
