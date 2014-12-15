#include "HockeyGame.h"
#include "SeasonXMLHandler.h"
#include "GameXmlHandler.h"
#include "ClockDialog.h"
#include "PpClockDialog.h"

HockeyGame::HockeyGame(QString awayName, QString homeName, QColor awayColor, QColor homeColor,
                       QString awayXML, QString homeXML, QString sponsor, QString announcers,
                       QString awayRank, QString homeRank, int screenWidth) :
    awayName(awayName), homeName(homeName), sponsor(sponsor), announcers(announcers), awayColor(awayColor),
    homeColor(homeColor), awayRank(awayRank), homeRank(homeRank),
    sb(awayColor, homeColor, awayName, homeName, sponsor, &gameClock, awayRank, homeRank),
    lt (awayColor, homeColor, screenWidth) {
    isFinal = false;
    awayScore = 0;
    homeScore = 0;
    homeSOG = 0;
    awaySOG = 0;
    period = 0;
    awayPlayersOnIce = 5;
    homePlayersOnIce = 5;
    timer.setTimerType(Qt::PreciseTimer);
    timer.setInterval(100);
    clockRunning = false;

    connect(&gameClock, SIGNAL(clockExpired()),
            this, SLOT(toggleClock()));
    connect(&timer, SIGNAL(timeout()), &gameClock, SLOT(tick()));
    connect(this, SIGNAL(periodChanged(int)), &sb, SLOT(updatePeriod(int)));
    connect(this, SIGNAL(awayScoreChanged(int)), &sb, SLOT(updateAwayScore(int)));
    connect(this, SIGNAL(homeScoreChanged(int)), &sb, SLOT(updateHomeScore(int)));
    connect(this, SIGNAL(penaltyChanged(int,Clock*,QString)), &sb, SLOT(preparePowerplayClock(int,Clock*,QString)));
    connect(this, SIGNAL(checkScoreboardPp()), this, SLOT(determinePpClockForScoreboard()));
    // Make teams...
    homeTeam = new HockeyTeam();
    awayTeam = new HockeyTeam();

    SeasonXMLHandler handler(homeTeam);
    QXmlSimpleReader r;
    r.setContentHandler(&handler);
    r.setErrorHandler(&handler);
    QFile file(homeXML);
    QXmlInputSource src(&file);
    r.parse(src);

    GameXmlHandler roadHandler(awayTeam);
    r.setContentHandler(&roadHandler);
    r.setErrorHandler(&roadHandler);
    QFile f2(awayXML);
    QXmlInputSource src2(&f2);
    r.parse(src2);
}

void
HockeyGame::awayGoal() {
    awayScore ++;
    timeEventHappened = period > 3 ? gameClock.getTimeSinceOtStarted() :
                                     gameClock.getTimeSincePdStarted();
    emit awayScoreChanged(awayScore);
    if (getHomeTeam()->getPlayerInGoal()) {
        homeTeam->getGoalie()->addGa();
    }
    awaySOG++;
    emit awaySogChanged(awaySOG);
}

void
HockeyGame::awayLoseGoal() {
    awayScore --;
    emit awayScoreChanged(awayScore);
    if (getHomeTeam()->getPlayerInGoal()) {
        homeTeam->getGoalie()->minusGa();
    }
    awaySOG--;
    emit awaySogChanged(awaySOG);
}

void
HockeyGame::homeGoal() {
    homeScore ++;
    timeEventHappened = period > 3 ? gameClock.getTimeSinceOtStarted() :
                                     gameClock.getTimeSincePdStarted();
    if (getAwayTeam()->getPlayerInGoal()) {
        awayTeam->getGoalie()->addGa();
    }
    homeSOG++;
    emit homeSogChanged(homeSOG);
    emit homeScoreChanged(homeScore);
}

void
HockeyGame::homeLoseGoal() {
    homeScore --;
    emit homeScoreChanged(homeScore);
    if (getAwayTeam()->getPlayerInGoal()) {
        awayTeam->getGoalie()->minusGa();
    }
    homeSOG--;
    emit homeSogChanged(homeSOG);
}

void
HockeyGame::addAwaySOG() {
    awaySOG++;
    if (getHomeTeam()->getPlayerInGoal()) {
        homeTeam->getGoalie()->addSave();
    }
    emit awaySogChanged(awaySOG);
}

void
HockeyGame::subAwaySOG() {
    awaySOG--;
    if (getHomeTeam()->getPlayerInGoal()) {
        homeTeam->getGoalie()->minusSave();
    }
    emit awaySogChanged(awaySOG);
}

void
HockeyGame::showAnnouncers() {
    if (announcers.contains("and") || announcers.contains("&")) {
        sb.changeTopBarText("Commentators: " + announcers);
    }
    else {
        sb.changeTopBarText("Commentator: " + announcers);
    }
}

void HockeyGame::gatherHomeSeasonStatsLt(int index)
{
    QList<QString> labels, numbers;
    HockeyPlayer* player = getHomeTeam()->getPlayer(index);
    labels.append("GP");
    numbers.append(QString::number(player->getGp()));
    if (player->getGaavg() == "NG") {
        labels.append("G");
        labels.append("A");
        labels.append("PTS");
        labels.append("+/-");
        numbers.append(QString::number(player->getGoals()+ player->getGoalsToday()));
        numbers.append(QString::number(player->getAssists()+ player->getAssistsToday()));
        numbers.append(QString::number(player->getPts() + player->getPtsToday()));
        numbers.append(player->getPlusMinus());
    }
    else {
        player->calcSvPct();
        labels.append("W-L");
        labels.append("SV");
        labels.append("SV %");
        labels.append("GAA");
        numbers.append(QString::number(player->getWins()) + "-" + QString::number(player->getLosses()));
        numbers.append(QString::number(player->getSaves()));
        numbers.append(QString::number(player->getSvPct(), 'g', 3) +"%");
        numbers.append(player->getGaavg());
    }
    lt.prepareForDisplay(player->getName(), player->getUni(), player->getYear(),
                         labels, numbers, true);
}

void HockeyGame::gatherHomeSeasonStatsSb(int index)
{
    HockeyPlayer* player = getHomeTeam()->getPlayer(index);
    QString text = player->getName() + " (" + getHomeName()+"): ";
    if (player->getGaavg() == "NG") {
        text += QString::number(player->getGoals() + player->getGoalsToday()) + " G, ";
        text += QString::number(player->getAssists() + player->getAssistsToday()) + " A, ";
        text += QString::number(player->getPim()+ player->getPimToday()) + " PIM";
    }
    else {
        text += QString::number(player->getWins()) + "-" + QString::number(player->getLosses())+", ";
        text += player->getGaavg() + " GAA, ";
        text += QString::number(player->getSvPct(), 'g', 3) + " SV %";
    }
    sb.changeTopBarText(text);
}

void HockeyGame::gatherHomeGameStatsLt(int index)
{
    HockeyPlayer* player = getHomeTeam()->getPlayer(index);
    QList<QString> labels, numbers;
    if (player->getGaavg() == "NG") {
        labels.append("G");
        labels.append("A");
        labels.append("PTS");
        labels.append("PIM");
        numbers.append(QString::number(player->getGoalsToday()));
        numbers.append(QString::number(player->getAssistsToday()));
        numbers.append(QString::number(player->getPtsToday()));
        numbers.append(QString::number(player->getPimToday()));
    }
    else {
        labels.append("GA");
        labels.append("SV");
        labels.append("SHOTS");
        numbers.append(QString::number(player->getGaToday()));
        numbers.append(QString::number(player->getSavesToday()));
        numbers.append(QString::number(player->getShotsFacedToday()));
    }
    lt.prepareForDisplay(player->getName(), player->getUni(), player->getYear(),
                         labels, numbers, true);
}

void HockeyGame::gatherAwayStatsLt(int index)
{
    HockeyPlayer* player = getAwayTeam()->getPlayer(index);
    QList<QString> labels, numbers;
    if (player->getGaavg() == "NG") {
        labels.append("G");
        labels.append("A");
        labels.append("PTS");
        labels.append("PIM");
        numbers.append(QString::number(player->getGoalsToday()));
        numbers.append(QString::number(player->getAssistsToday()));
        numbers.append(QString::number(player->getPtsToday()));
        numbers.append(QString::number(player->getPimToday()));
    }
    else {
        labels.append("GA");
        labels.append("SV");
        labels.append("SHOTS");
        numbers.append(QString::number(player->getGaToday()));
        numbers.append(QString::number(player->getSavesToday()));
        numbers.append(QString::number(player->getShotsFacedToday()));
    }
    lt.prepareForDisplay(player->getName(), player->getUni(), "",
                         labels, numbers, false);
}

void HockeyGame::gatherHomeGameStatsSb(int index)
{
    HockeyPlayer* player = getHomeTeam()->getPlayer(index);
    QString text = player->getName() + " (" + getHomeName()+"): ";
    if (player->getGaavg() == "NG") {
        text += QString::number(player->getGoalsToday()) + " G, ";
        text += QString::number(player->getAssistsToday()) + " A, ";
        text += QString::number(player->getPimToday()) + " PIM";
    }
    else {
        text += QString::number(player->getGaToday()) + " GA, ";
        text += QString::number(player->getSavesToday()) + " SAVES";
    }
    sb.changeTopBarText(text);
}

void HockeyGame::gatherAwayGameStatsSb(int index)
{
    HockeyPlayer* player = getAwayTeam()->getPlayer(index);
    QString text = player->getName() + " (" + getAwayName()+"): ";
    if (player->getGaavg() == "NG") {
        text += QString::number(player->getGoalsToday()) + " G, ";
        text += QString::number(player->getAssistsToday()) + " A, ";
        text += QString::number(player->getPimToday()) + " PIM";
    }
    else {
        text += QString::number(player->getGaToday()) + " GA, ";
        text += QString::number(player->getSavesToday()) + " SAVES";
    }
    sb.changeTopBarText(text);
}

void HockeyGame::prepareHomeGoalText(int scorer, int a1, int a2)
{
    HockeyPlayer* goalScorer = homeTeam->getPlayer(scorer);
    HockeyPlayer* ast1 = homeTeam->getPlayer(a1);
    HockeyPlayer* ast2 = homeTeam->getPlayer(a2);
    QString text = getHomeName() + " GOAL: " + goalScorer->getName() + " ";
    if (ast1 != NULL) {
        text += "(" + ast1->getName().mid(ast1->getName().indexOf(" ")+1);
        if (ast2 != NULL) {
            text += ", " + ast2->getName().mid(ast2->getName().indexOf(" ")+1);
        }
        text += ") ";
    }
    else {
        text += "(Unassisted) ";
    }
    text += timeEventHappened;
    sb.changeTopBarText(text);

}

void HockeyGame::prepareAwayGoalText(int scorer, int a1, int a2)
{
    HockeyPlayer* goalScorer = awayTeam->getPlayer(scorer);
    HockeyPlayer* ast1 = awayTeam->getPlayer(a1);
    HockeyPlayer* ast2 = awayTeam->getPlayer(a2);
    QString text = getAwayName() + " GOAL: " + goalScorer->getName() + " ";
    if (ast1 != NULL) {
        text += "(" + ast1->getName().mid(ast1->getName().indexOf(" ")+1);
        if (ast2 != NULL) {
            text += ", " + ast2->getName().mid(ast2->getName().indexOf(" ")+1);
        }
        text += ") ";
    }
    else {
        text += "(Unassisted) ";
    }
    text += timeEventHappened;
    sb.changeTopBarText(text);
}

void HockeyGame::prepareHomePenaltyText(int pIndex, QString penalty)
{
    sb.changeTopBarText( getHomeName() + " PENALTY: " + homeTeam->getPlayer(pIndex)->getName() + " ("
                         + penalty +") " + timeEventHappened );
}

void HockeyGame::prepareAwayPenaltyText(int pIndex, QString penalty)
{
    sb.changeTopBarText( getAwayName() + " PENALTY: " + awayTeam->getPlayer(pIndex)->getName() + " ("
                         + penalty +") " + timeEventHappened );
}

void HockeyGame::gatherPpStats()
{
    QString ppStat, pkStat;
    if (homePlayersOnIce > awayPlayersOnIce) {
        ppStat = QString::number(homeTeam->getPpg()) + "-" + QString::number(homeTeam->getPpopp())
                + ", " + QString::number(homeTeam->getPpPct(), 'g', 3) +"%";
        pkStat = QString::number(awayTeam->getPk()) + "-" + QString::number(awayTeam->getPkopp())
                + ", " + QString::number(awayTeam->getPkPct(), 'g', 3) +"%";
        if (homeTeam->getPpoppToday() > 0) {
            ppStat += "\nToday: " + QString::number(homeTeam->getPpgToday()) + "-" + QString::number(homeTeam->getPpoppToday());
            pkStat += "\nToday: " + QString::number(awayTeam->getPkToday()) + "-" + QString::number(awayTeam->getPkoppToday());
        }
        lt.prepareForPpComp(getAwayName(), "PENALTY KILL", pkStat, getHomeName(), "POWERPLAY", ppStat);
    }
    else if (homePlayersOnIce < awayPlayersOnIce) {
        ppStat = QString::number(awayTeam->getPpg()) + "-" + QString::number(awayTeam->getPpopp())
                + ", " + QString::number(awayTeam->getPpPct(), 'g', 3) +"%";
        pkStat = QString::number(homeTeam->getPk()) + "-" + QString::number(homeTeam->getPkopp())
                + ", " + QString::number(homeTeam->getPkPct(), 'g', 3) +"%";
        if (awayTeam->getPpoppToday() > 0) {
            ppStat += "\nToday: " + QString::number(awayTeam->getPpgToday()) + "-" + QString::number(awayTeam->getPpoppToday());
            pkStat += "\nToday: " + QString::number(homeTeam->getPkToday()) + "-" + QString::number(homeTeam->getPkoppToday());
        }
        lt.prepareForPpComp(getAwayName(), "POWERPLAY", ppStat, getHomeName(), "PENALTY KILL", pkStat);
    }
}

Clock* HockeyGame::getGameClock()
{
    return &gameClock;
}

HockeyTeam* HockeyGame::getAwayTeam() const
{
    return awayTeam;
}

HockeyTeam* HockeyGame::getHomeTeam() const
{
    return homeTeam;
}


QString HockeyGame::getAwayName() const
{
    return awayName;
}

void HockeyGame::setAwayName(const QString& value)
{
    awayName = value;
}

QString HockeyGame::getHomeName() const
{
    return homeName;
}

void HockeyGame::setHomeName(const QString& value)
{
    homeName = value;
}

QString HockeyGame::getAnnouncers() const
{
    return announcers;
}

void HockeyGame::setAnnouncers(const QString& value)
{
    announcers = value;
}

QString HockeyGame::getSponsor() const
{
    return sponsor;
}

void HockeyGame::setSponsor(const QString& value)
{
    sponsor = value;
}

LowerThird* HockeyGame::getLt()
{
    return &lt;
}


Scoreboard* HockeyGame::getSb()
{
    return &sb;
}

void
HockeyGame::addHomeSOG() {
    homeSOG++;
    if (awayTeam->getPlayerInGoal()) {
        awayTeam->getGoalie()->addSave();
    }
    emit homeSogChanged(homeSOG);
}

void
HockeyGame::subHomeSOG() {
    homeSOG--;
    if (awayTeam->getPlayerInGoal()) {
        awayTeam->getGoalie()->minusSave();
    }
    emit homeSogChanged(homeSOG);
}

void
HockeyGame::advancePeriod() {
    period++;
    isFinal = false;
    deleteExpiredPenalties();
    emit periodChanged(period);
}

void
HockeyGame::rewindPeriod() {
    period--;
    isFinal = false;
    deleteExpiredPenalties();
    emit periodChanged(period);
}

void
HockeyGame::addHomePenalty(int time) {
    Clock* pc = new Clock(time);
    homePlayersOnIce --;
    timeEventHappened = period > 3 ? gameClock.getTimeSinceOtStarted() :
                                     gameClock.getTimeSincePdStarted();
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
    timeEventHappened = period > 3 ? gameClock.getTimeSinceOtStarted() :
                                     gameClock.getTimeSincePdStarted();
    awayPlayersOnIce --;
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
            disconnect(&timer, SIGNAL(timeout()), awayPenalty.at(i), SLOT(tick()));
        }
    }
    awayPlayersOnIce++;
    determinePpClockForScoreboard();
}

void
HockeyGame::homePenaltyExpired() {

    for (int i = 0; i < homePenalty.size(); i++) {
        if (homePenalty.at(i)->getTimeLeft() == 0) {
            disconnect(&timer, SIGNAL(timeout()), homePenalty.at(i), SLOT(tick()));
        }
    }
    homePlayersOnIce++;


//    for (int i = 0; i < homePenalty.size(); i++) {
//        if (homePenalty.at(i)->getTimeLeft() == 0) {
//            delete homePenalty.at(i);
//            homePenalty.removeAt(i);
//        }
//    }
    determinePpClockForScoreboard();
}

void
HockeyGame::determinePpClockForScoreboard() {
    int ppPos;
    QString description = "";
    //homePlayersOnIce = 5 - homePenalty.size();
    //awayPlayersOnIce = 5 - awayPenalty.size();
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
            description = QString::number(homePlayersOnIce) + "-ON-" +
                    QString::number(awayPlayersOnIce);
        }
    }
    // away pp
    else if (awayPlayersOnIce > homePlayersOnIce){
        ppPos = 1;
        // typical pp
        if (homePlayersOnIce == 4) {
            description = "POWERPLAY";
        }
        else {
            description = QString::number(awayPlayersOnIce, 10) + "-ON-" +
                    QString::number(homePlayersOnIce);
        }
    }
    else {
        ppPos = 0;
    }
    Clock* ppClock = getLowestPpClock();
    emit penaltyChanged(ppPos, ppClock, description);

}

void HockeyGame::displayPenaltyEditor()
{
    PpClockDialog ppDiag(this);
    ppDiag.exec();
}

void HockeyGame::makeFinal()
{
    isFinal = true;
}

void HockeyGame::deleteExpiredPenalties()
{
        for (int i = 0; i < awayPenalty.size(); i++) {
        if (awayPenalty.at(i)->getTimeLeft() == 0) {
            Clock* toDelete = awayPenalty.at(i);
            awayPenalty.removeAt(i);
            delete toDelete;
            i--;
        }
    }
    for (int i = 0; i < homePenalty.size(); i++) {
        if (homePenalty.at(i)->getTimeLeft() == 0) {
            Clock* toDelete = homePenalty.at(i);
            homePenalty.removeAt(i);
            delete toDelete;
            i--;
        }
    }
    homePlayersOnIce = 5 - homePenalty.size();
    awayPlayersOnIce = 5 - awayPenalty.size();
}
int HockeyGame::getAwaySOG() const
{
    return awaySOG;
}

void HockeyGame::setAwaySOG(int value)
{
    awaySOG = value;
    emit awaySogChanged(awaySOG);
}

int HockeyGame::getHomeSOG() const
{
    return homeSOG;
}

void HockeyGame::setHomeSOG(int value)
{
    homeSOG = value;
    emit homeSogChanged(homeSOG);
}

bool HockeyGame::getIsFinal() const
{
    return isFinal;
}

void HockeyGame::setIsFinal(bool value)
{
    isFinal = value;
}

int HockeyGame::getPeriod() const
{
    return period;
}

void HockeyGame::setPeriod(int value)
{
    period = value;
}

int HockeyGame::getHomeScore() const
{
    return homeScore;
}

void HockeyGame::setHomeScore(int value)
{
    homeScore = value;
}

int HockeyGame::getAwayScore() const
{
    return awayScore;
}

void HockeyGame::setAwayScore(int value)
{
    awayScore = value;
}

QColor HockeyGame::getAwayColor() const
{
    return awayColor;
}

void HockeyGame::setAwayColor(const QColor& value)
{
    awayColor = value;
}

QColor HockeyGame::getHomeColor() const
{
    return homeColor;
}

void HockeyGame::setHomeColor(const QColor& value)
{
    homeColor = value;
}

QString HockeyGame::getAwayRank() const
{
    return awayRank;
}

void HockeyGame::setAwayRank(const QString& value)
{
    awayRank = value;
}

QString HockeyGame::getHomeRank() const
{
    return homeRank;
}

void HockeyGame::setHomeRank(const QString& value)
{
    homeRank = value;
}

QList<Clock*> HockeyGame::getHomePenalty() const
{
    return homePenalty;
}

void HockeyGame::setHomePenalty(const QList<Clock*>& value)
{
    homePenalty = value;
}

QList<Clock*> HockeyGame::getAwayPenalty() const
{
    return awayPenalty;
}

void HockeyGame::setAwayPenalty(const QList<Clock*>& value)
{
    awayPenalty = value;
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
    for (int i = 0; i < homePenalty.size() && homePlayersOnIce < 5; i++) {
        if (i == 0 && homePenalty.at(i)->getTimeLeft() != 0) {
            homePP = homePenalty.at(i);
        }
        else {
            if (homePenalty.at(i)->getTimeLeft() != 0 && homePP == NULL) {
                homePP = homePenalty.at(i);
            }
            else if (homePP != NULL && homePenalty.at(i)->getTimeLeft() < homePP->getTimeLeft()) {
                homePP = homePenalty.at(i);
            }
        }
    }
    for (int i = 0; i < awayPenalty.size() && awayPlayersOnIce < 5; i++) {
        if (i == 0 && awayPenalty.at(i)->getTimeLeft() != 0) {
            awayPP = awayPenalty.at(i);
        }
        else {
            if (awayPenalty.at(i)->getTimeLeft() != 0 && awayPP == NULL) {
                awayPP = awayPenalty.at(i);
            }
            else if (awayPP != NULL && awayPenalty.at(i)->getTimeLeft() < awayPP->getTimeLeft()) {
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
