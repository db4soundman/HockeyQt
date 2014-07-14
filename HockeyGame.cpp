#include "HockeyGame.h"
#include "SeasonXMLHandler.h"
#include "GameXmlHandler.h"
#include "ClockDialog.h"
#include "PpClockDialog.h"

HockeyGame::HockeyGame(QString awayName, QString homeName, QColor awayColor, QColor homeColor,
                       QString awayXML, QString homeXML, QString sponsor, QString announcers,
                       QString awayRank, QString homeRank) :
    awayName(awayName), homeName(homeName), sponsor(sponsor), announcers(announcers), awayColor(awayColor),
    homeColor(homeColor), awayRank(awayRank), homeRank(homeRank),
    sb(awayColor, homeColor, awayName, homeName, sponsor, &gameClock) {
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
}

void
HockeyGame::awayLoseGoal() {
    awayScore --;
    emit awayScoreChanged(awayScore);
}

void
HockeyGame::homeGoal() {
    homeScore ++;
    timeEventHappened = period > 3 ? gameClock.getTimeSinceOtStarted() :
                                     gameClock.getTimeSincePdStarted();
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
        numbers.append(QString::number(player->getGoals()));
        numbers.append(QString::number(player->getAssists()));
        numbers.append(QString::number(player->getPts()));
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
                         labels, numbers, homeColor);
}

void HockeyGame::gatherHomeSeasonStatsSb(int index)
{
    HockeyPlayer* player = getHomeTeam()->getPlayer(index);
    QString text = player->getName() + " (" + getHomeName()+"): ";
    if (player->getGaavg() == "NG") {
        text += QString::number(player->getGoals()) + " G, ";
        text += QString::number(player->getAssists()) + " A, ";
        text += QString::number(player->getPenalties()) + " PTY";
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
        labels.append("PTY");
        numbers.append(QString::number(player->getGoalsToday()));
        numbers.append(QString::number(player->getAssistsToday()));
        numbers.append(QString::number(player->getPtsToday()));
        numbers.append(QString::number(player->getPenaltiesToday()));
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
                         labels, numbers, homeColor);
}

void HockeyGame::gatherAwayStatsLt(int index)
{
    HockeyPlayer* player = getAwayTeam()->getPlayer(index);
    QList<QString> labels, numbers;
    if (player->getGaavg() == "NG") {
        labels.append("G");
        labels.append("A");
        labels.append("PTS");
        labels.append("PTY");
        numbers.append(QString::number(player->getGoalsToday()));
        numbers.append(QString::number(player->getAssistsToday()));
        numbers.append(QString::number(player->getPtsToday()));
        numbers.append(QString::number(player->getPenaltiesToday()));
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
                         labels, numbers, awayColor);
}

void HockeyGame::gatherHomeGameStatsSb(int index)
{
    HockeyPlayer* player = getHomeTeam()->getPlayer(index);
    QString text = player->getName() + " (" + getHomeName()+"): ";
    if (player->getGaavg() == "NG") {
        text += QString::number(player->getGoalsToday()) + " G, ";
        text += QString::number(player->getAssistsToday()) + " A, ";
        text += QString::number(player->getPenaltiesToday()) + " PTY";
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
        text += QString::number(player->getPenaltiesToday()) + " PTY";
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
