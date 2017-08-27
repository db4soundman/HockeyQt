#include "HockeyGame.h"
#include "SeasonXMLHandler.h"
#include "GameXmlHandler.h"
#include "ClockDialog.h"
#include "PpClockDialog.h"
#include "GraphicChooser.txt"
#include "console.h"

HockeyGame::HockeyGame(QString awayName, QString homeName, QColor awayColor, QColor homeColor,
                       QString awayXML, QString homeXML, QString sponsor, QString announcers,
                       QString awayRank, QString homeRank, int screenWidth, QPixmap awayLogo, QString hsName, QString asName) :
    awayName(awayName), homeName(homeName), sponsor(sponsor), announcers(announcers), awayColor(awayColor),
    homeColor(homeColor), awayRank(awayRank), homeRank(homeRank),
    sb(awayColor, homeColor, awayName, homeName, sponsor, &gameClock, awayRank, homeRank, awayLogo), homeShortName(hsName),
    awayShortName(asName), comparisonPreview(awayColor, homeColor, awayLogo, true),
    #ifdef GRADIENT_LOOK
    lt (awayColor, homeColor, screenWidth)
  #else
    lt(awayColor, homeColor, screenWidth, awayLogo), previewLt(awayColor, homeColor, screenWidth, awayLogo)
  #endif
{
    useClock = true;
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
    cgTimer.setTimerType(Qt::PreciseTimer);
    cgTimer.setInterval(100);
    tricasterRefresh.setInterval(1000*30);
    clockRunning = false;
    penaltiesActive = false;

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
    HockeyPlayer* empty = new HockeyPlayer();
    empty->setName("No NAME");
    homeTeam->addPlayer(empty);
    SeasonXMLHandler roadHandler(awayTeam);
    r.setContentHandler(&roadHandler);
    r.setErrorHandler(&roadHandler);
    QFile f2(awayXML);
    QXmlInputSource src2(&f2);
    r.parse(src2);
    awayTeam->addPlayer(empty);
}

void
HockeyGame::awayGoal() {
    awayScore ++;
    if (useClock)
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
    if (useClock)
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

void HockeyGame::showSogComparison()
{
    QList<QString> stats;
    stats.append(QString::number(awaySOG));
    stats.append(QString::number(homeSOG));
    comparisonGraphic->prepareStandardComp(getAwayTri(), getHomeTri(), stats, "Shots on Goal");
}

QPixmap HockeyGame::getSogComparisonPreview()
{
    QList<QString> stats;
    stats.append(QString::number(awaySOG));
    stats.append(QString::number(homeSOG));
    comparisonPreview.prepareStandardComp(getAwayTri(), getHomeTri(), stats, "Shots on Goal");
    QPixmap graphic(comparisonPreview.getWidth(), comparisonPreview.getHeight());
    graphic.fill(QColor(0,0,0,0));
    QPainter painter(&graphic);
    comparisonPreview.paintPreview(&painter);
    return graphic.scaled(comparisonPreview.getWidth()/2, comparisonPreview.getHeight()/2);
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

QString HockeyGame::getSeasonPopText(int index, bool home)
{
    HockeyPlayer* player = home ? getHomeTeam()->getPlayer(index) : getAwayTeam()->getPlayer(index);
    QString text = player->getName() + " (" + (home ? getHomeTri() : getAwayTri()) +"): ";
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
    return text;
}

QString HockeyGame::getGamePopText(int index, bool home)
{
    HockeyPlayer* player = home ? getHomeTeam()->getPlayer(index) :
                                  getAwayTeam()->getPlayer(index);
    QString text = home ? player->getName() + " (" + getHomeTri()+"): " :
                          player->getName() + " (" + getAwayTri()+"): ";
    if (player->getGaavg() == "NG") {
        text += QString::number(player->getGoalsToday()) + " G, ";
        text += QString::number(player->getAssistsToday()) + " A, ";
        text += QString::number(player->getPimToday()) + " PIM";
    }
    else {
        text += QString::number(player->getGaToday()) + " GA, ";
        text += QString::number(player->getSavesToday()) + " SAVES";
    }
    return text;
}

QPixmap HockeyGame::getSeasonPreviewLt(int index, bool home)
{
    QList<QString> labels, numbers;
    HockeyPlayer* player = home ? getHomeTeam()->getPlayer(index) : getAwayTeam()->getPlayer(index);
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
        numbers.append(QString::number(player->getSvPct(), 'g', 3));
        numbers.append(player->getGaavg());
    }
    previewLt.prepareForDisplay(player->getName(), player->getUni(), player->getYear(),
                         labels, numbers, home, false);
    QPixmap preview(previewLt.getWidth(), previewLt.getHeight());
    QPainter painter(&preview);
    previewLt.paintPreview(&painter);
    return preview;
}

QPixmap HockeyGame::getGamePreviewLt(int index, bool home)
{
    HockeyPlayer* player = home ? getHomeTeam()->getPlayer(index) : getAwayTeam()->getPlayer(index);
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

    previewLt.prepareForDisplay(player->getName(), player->getUni(), player->getYear(),
                         labels, numbers, home, false);
    QPixmap preview(previewLt.getWidth(), previewLt.getHeight());
    QPainter painter(&preview);
    previewLt.paintPreview(&painter);
    return preview;
}

void HockeyGame::gatherSeasonStatsLt(int index, bool home)
{
    QList<QString> labels, numbers;
    HockeyPlayer* player = home ? getHomeTeam()->getPlayer(index) : getAwayTeam()->getPlayer(index);
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
        numbers.append(QString::number(player->getSvPct(), 'g', 3));
        numbers.append(player->getGaavg());
    }
    lt.prepareForDisplay(player->getName(), player->getUni(), player->getYear(),
                         labels, numbers, home);
}

void HockeyGame::gatherSeasonStatsSb(int index, bool home)
{

    sb.changeTopBarText(getSeasonPopText(index, home));
}

void HockeyGame::gatherGameStatsLt(int index, bool home)
{
    HockeyPlayer* player = home ? getHomeTeam()->getPlayer(index) : getAwayTeam()->getPlayer(index);
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
                         labels, numbers, home);
}

void HockeyGame::gatherGameStatsSb(int index, bool home)
{

    sb.changeTopBarText(getGamePopText(index, home));
}

QString HockeyGame::getGoalText(int scorer, int a1, int a2, bool home)
{
    HockeyTeam* team = home ? homeTeam : awayTeam;
    HockeyPlayer* goalScorer = team->getPlayer(scorer);
    HockeyPlayer* ast1 = team->getPlayer(a1);
    HockeyPlayer* ast2 = team->getPlayer(a2);
    QString text = (home ? getHomeTri() : getAwayTri()) + " GOAL: " + goalScorer->getName() + " ";
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
    return text;
}

void HockeyGame::prepareHomeGoalText(int scorer, int a1, int a2)
{

    sb.changeTopBarText(getGoalText(scorer,a1,a2,true));

}

void HockeyGame::prepareAwayGoalText(int scorer, int a1, int a2)
{
    sb.changeTopBarText(getGoalText(scorer,a1,a2,false));
}

QString HockeyGame::getPenaltyText(int pIndex, QString penalty, bool home)
{
    HockeyTeam* team = home ? homeTeam: awayTeam;
    return ((home ? getHomeTri() : getAwayTri()) + " PENALTY: " + team->getPlayer(pIndex)->getName() + " ("
            + penalty +") " + timeEventHappened);
}

void HockeyGame::prepareHomePenaltyText(int pIndex, QString penalty)
{
    sb.changeTopBarText(getPenaltyText(pIndex, penalty, true));
}

void HockeyGame::prepareAwayPenaltyText(int pIndex, QString penalty)
{
    sb.changeTopBarText(getPenaltyText(pIndex, penalty, false));
}
#ifdef GRADIENT_LOOK
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
#else
void HockeyGame::gatherPpStats()
{
    // Order: Away season, home season, away today, home today.
    QList<QString> stats;
    QString ppStat, pkStat;
    if (homePlayersOnIce > awayPlayersOnIce) {
        ppStat = QString::number(homeTeam->getPpPct(), 'g', 3) +"%";
        pkStat = QString::number(awayTeam->getPkPct(), 'g', 3) +"%";
        stats.append(pkStat);
        stats.append(ppStat);
        if (homeTeam->getPpoppToday() > 0) {
            stats.append("Today: " + QString::number(awayTeam->getPkToday()) + "-" + QString::number(awayTeam->getPkoppToday()));
            stats.append("Today: " + QString::number(homeTeam->getPpgToday()) + "-" + QString::number(homeTeam->getPpoppToday()));

        }
        comparisonGraphic->prepareStandardComp("PENALTY KILL", "POWER PLAY", stats);
    }
    else if (homePlayersOnIce < awayPlayersOnIce) {
        stats.append(QString::number(awayTeam->getPpPct(), 'g', 3) +"%");
        stats.append(QString::number(homeTeam->getPkPct(), 'g', 3) +"%");
        if (awayTeam->getPpoppToday() > 0) {
            stats.append("Today: " + QString::number(awayTeam->getPpgToday()) + "-" + QString::number(awayTeam->getPpoppToday()));
            stats.append("Today: " + QString::number(homeTeam->getPkToday()) + "-" + QString::number(homeTeam->getPkoppToday()));
        }
      comparisonGraphic->prepareStandardComp("POWER PLAY","PENALTY KILL", stats);
    }
}
#endif

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

void HockeyGame::connectWithSerialHandler(SerialConsole *console)
{
    connect(console, SIGNAL(serialConnected()), this->getGameClock(), SLOT(usingSerialClock()));
    connect(console, SIGNAL(serialConnected()), this, SIGNAL(usingAllSport()));
    connect(console, SIGNAL(serialConnected()), &sb, SLOT(usingAllSport()));

    connect(console, SIGNAL(dataReceived(QByteArray)), this, SLOT(parseAllSportCG(QByteArray)));

    connect(console, SIGNAL(serialDisconnected()), this->getGameClock(), SLOT(noLongerUsingSerialClock()));
    connect(console, SIGNAL(serialDisconnected()), this, SIGNAL(usingInternalClock()));
    connect(console, SIGNAL(serialDisconnected()), &sb, SLOT(usingInternalClocks()));
    connect(console, SIGNAL(serialDisconnected()), &cgTimer, SLOT(stop()));
    serialConsole = console;
}

void HockeyGame::parseAllSportCG(QByteArray data)
{
    try {
        QString clock = data.mid(1, 7);
        bool stopped = data.mid(8,1) == "s";
        int homeScoreS = data.mid(9,2).trimmed().toInt();
        int awayScoreS = data.mid(11,2).trimmed().toInt();
        int homeTol = data.mid(13,1).toInt();
        int awayTol = data.mid(14,1).toInt();
        int hSog = data.mid(15,2).toInt();
        int aSog = data.mid(17,2).toInt();
        int cgPeriod = data.mid(19,2).toInt();
        QString penClock="";

        bool penH1,penH2,penA1,penA2;
        int homePlayer1 = data.mid(21,2).toInt(&penH1);
        QString homePen1 = data.mid(23,5).trimmed();
        int homePlayer2 = data.mid(28,2).toInt(&penH2);
        QString homePen2 = data.mid(30,5).trimmed();
        int awayPlayer1 = data.mid(35,2).toInt(&penA1);
        QString awayPen1 = data.mid(37,5).trimmed();
        int awayPlayer2 = data.mid(42,2).toInt(&penA2);
        QString awayPen2 = data.mid(44,5).trimmed();

        int awayInTheBox = 0;
        int homeInTheBox = 0;
        QSet<int>awayTemp,homeTemp;
        bool penalty = false;
        if (penaltiesActive || (!penaltiesActive && stopped)) {
            if (penA1){
                awayInTheBox++;
                awayTemp.insert(awayPlayer1);
                if (!awayPlayersInBox.contains(awayPlayer1)) triggerNewPenalty();
                awayPlayersInBox.insert(awayPlayer1);
                penalty = true;
            }
            if (penA2) {
                awayInTheBox++;
                awayTemp.insert(awayPlayer2);
                if (!awayPlayersInBox.contains(awayPlayer2)) triggerNewPenalty();
                awayPlayersInBox.insert(awayPlayer2);
            }
            awayPlayersInBox = awayPlayersInBox.intersect(awayTemp);

            if (penH1){
                homeInTheBox++;
                homeTemp.insert(homePlayer1);
                if (!homePlayersInBox.contains(homePlayer1)) triggerNewPenalty();
                homePlayersInBox.insert(homePlayer1);
                penalty = true;
            }
            if (penH2){
                homeInTheBox++;
                homeTemp.insert(homePlayer2);
                if (!homePlayersInBox.contains(homePlayer2)) triggerNewPenalty();
                homePlayersInBox.insert(homePlayer2);
            }
            if (penalty) {
                if (penA1 && penH1) {
                    if (awayPen1 < homePen1) {
                        penClock = awayPen1.trimmed();
                    } else {
                        penClock = homePen1.trimmed();
                    }

                } else if(penA1) {
                    penClock = awayPen1.trimmed();
                } else {
                    penClock = homePen1.trimmed();
                }
            } else if (penaltiesActive) {
                // There were active penalties, but not anymore
            }
            penaltiesActive = penalty;
            determinePpClockAllSport(penClock);
        }
        gameClock.setClock(clock.trimmed());
        if (homeScore != homeScoreS) {
            while (homeScore < homeScoreS) {
                homeGoal();
            }
            while (homeScore > homeScoreS) {
                homeLoseGoal();
            }

        }
        if (awayScore != awayScoreS) {
            while (awayScore < awayScoreS) {
                awayGoal();
            }
            while (awayScore > awayScoreS) {
                awayLoseGoal();
            }

        }
        if (homeSOG != hSog) {
            while (homeSOG < hSog) {
                addHomeSOG();
            }
            while (homeSOG > hSog) {
                subHomeSOG();
            }
        }
        if (awaySOG != aSog) {
            while (awaySOG < aSog) {
                addAwaySOG();
            }
            while (awaySOG > aSog) {
                subAwaySOG();
            }
        }
        //toggleCgPenaltyClocks(!stopped);
    } catch (...) {
        serialConsole->getConsole()->putData(data);
        serialConsole->closeSerialPort();
        serialConsole->openSerialPort();
    }

}

void HockeyGame::prepareFaceoffComparison(int awayWins, int homeWins)
{
    QList<QString> stats;
    stats.append(QString::number(awayWins));
    stats.append(QString::number(homeWins));
    prepareSameStatComp(stats, "FACEOFF WINS");
}

QPixmap HockeyGame::getFaceoffCompPreview(int awayWins, int homeWins)
{
    QList<QString> stats;
    stats.append(QString::number(awayWins));
    stats.append(QString::number(homeWins));
    prepareSameStatComp(stats, "FACEOFF WINS", false);
    QPixmap graphic(comparisonPreview.getWidth(), comparisonPreview.getHeight());
    graphic.fill(QColor(0,0,0,0));
    QPainter painter(&graphic);
    comparisonPreview.paintPreview(&painter);
    return graphic.scaled(comparisonPreview.getWidth()/2, comparisonPreview.getHeight()/2);
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
    if (useClock)
        timeEventHappened = period > 3 ? gameClock.getTimeSinceOtStarted() :
                                         gameClock.getTimeSincePdStarted();
    homePenalty.append(pc);
    connect(&timer, SIGNAL(timeout()),
            pc, SLOT(tick()));
    connect(&cgTimer, SIGNAL(timeout()),
            pc, SLOT(tick()));
    connect(pc, SIGNAL(clockExpired()),
            this, SLOT(homePenaltyExpired()));
    determinePpClockForScoreboard();
}

void
HockeyGame::addAwayPenalty(int time) {

    Clock* pc = new Clock(time);
    if (useClock)
        timeEventHappened = period > 3 ? gameClock.getTimeSinceOtStarted() :
                                         gameClock.getTimeSincePdStarted();
    awayPlayersOnIce --;
    awayPenalty.append(pc);
    connect(&timer, SIGNAL(timeout()),
            pc, SLOT(tick()));
    connect(&cgTimer, SIGNAL(timeout()),
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
            disconnect(&cgTimer, SIGNAL(timeout()), awayPenalty.at(i), SLOT(tick()));
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
            disconnect(&cgTimer, SIGNAL(timeout()), homePenalty.at(i), SLOT(tick()));
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
            description = "POWER PLAY";
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
            description = "POWER PLAY";
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

void HockeyGame::changeUseClock(bool uc)
{
    useClock = uc;
    emit clockInUse(useClock);
    if (!uc)
        tricasterRefresh.start();
    else
        tricasterRefresh.stop();
}

void HockeyGame::removeFirstHomePenalty()
{
    for (int i = 0; i < homePenalty.size(); i++) {
        if (homePenalty.at(i)->getTimeLeft() != 0) {
            Clock* toDelete = homePenalty.at(i);
            toDelete->setClock(0,0,0);
            break;
        }
    }
}

void HockeyGame::removeFirstAwayPenalty()
{
    for (int i = 0; i < awayPenalty.size(); i++) {
        if (awayPenalty.at(i)->getTimeLeft() != 0) {
            Clock* toDelete = awayPenalty.at(i);
            toDelete->setClock(0,0,0);
            break;
        }
    }
}

void HockeyGame::removeNewestHomePenalty()
{
    for (int i = homePenalty.size()-1; i > -1 ; i--) {
        if (homePenalty.at(i)->getTimeLeft() != 0) {
            Clock* toDelete = homePenalty.at(i);
            toDelete->setClock(0,0,0);
            break;
        }
    }
    //determinePpClockForScoreboard();
}

void HockeyGame::removeNewestAwayPenalty()
{
    for (int i = awayPenalty.size()-1; i > -1 ; i--) {
        if (awayPenalty.at(i)->getTimeLeft() != 0) {
            Clock* toDelete = awayPenalty.at(i);
            toDelete->setClock(0,0,0);
            break;
        }
    }
    //determinePpClockForScoreboard();
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

ComparisonGraphic *HockeyGame::getComparisonPreview()
{
    return &comparisonPreview;
}

LowerThird *HockeyGame::getPreviewLt()
{
    return &previewLt;
}

ComparisonGraphic *HockeyGame::getComparisonGraphic() const
{
    return comparisonGraphic;
}

void HockeyGame::setComparisonGraphic(ComparisonGraphic *value)
{
    comparisonGraphic = value;
}

void HockeyGame::toggleCgPenaltyClocks(bool isOn)
{
    if (!isOn) {
        cgTimer.stop();
    } else if (!cgTimer.isActive() && getSb()->getShowClock()) {
        cgTimer.start();
    }
}
QTimer *HockeyGame::getTricasterRefresh()
{
    return &tricasterRefresh;
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

QString HockeyGame::getAwayTri() const
{
    return awayName.length() > 6 ? awayShortName : awayName;
}

QString HockeyGame::getHomeTri() const
{
    return homeName.length() > 6 ? homeShortName : homeName;
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
            else if (homePenalty.at(i)->getTimeLeft() == 0 && homePP != NULL) {
               continue;
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
            else if (awayPenalty.at(i)->getTimeLeft() == 0 && awayPP != NULL) {
                continue;
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

void HockeyGame::prepareSameStatComp(QList<QString> stats, QString statName, bool goLive)
{
    if (goLive) {
        comparisonGraphic->prepareStandardComp(getAwayTri(), getHomeTri(), stats, statName);
    }
    else {
        comparisonPreview.prepareStandardComp(getAwayTri(), getHomeTri(), stats, statName);
    }
}

void HockeyGame::triggerNewPenalty()
{
    timeEventHappened = period > 3 ? gameClock.getTimeSinceOtStarted() :
                                     gameClock.getTimeSincePdStarted();
}

void HockeyGame::determinePpClockAllSport(QString clock)
{
    int ppPos;
    QString description = "";
    QString num;
    if (period != 5) {
        homePlayersOnIce = 5 - homePlayersInBox.size();
        awayPlayersOnIce = 5 - awayPlayersInBox.size();
    } else {
        // This can vary based on # of penalties and whether the clock is running...
        homePlayersOnIce = 3 + awayPlayersInBox.size() - homePlayersInBox.size();
        awayPlayersOnIce = 3 + homePlayersInBox.size() - awayPlayersInBox.size();
    }

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
        if (awayPlayersOnIce == 4 && period != 5) {
            description = "POWER PLAY";
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
        if (homePlayersOnIce == 4 && period != 5) {
            description = "POWER PLAY";
        }
        else {
            description = QString::number(awayPlayersOnIce, 10) + "-ON-" +
                    QString::number(homePlayersOnIce);
        }
    }
    else {
        ppPos = 0;
    }
    sb.setSerialPowerPlay(ppPos,clock,description);
}
