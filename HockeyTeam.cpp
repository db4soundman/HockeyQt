#include "HockeyTeam.h"

HockeyTeam::HockeyTeam() {
    ppgToday = ppoppToday = pkToday = pkoppToday = 0;
    timeoutsLeft = 1;
    ppg = 0;
    ppopp = 0;
    pk=0;
    pkopp=0;
}

HockeyPlayer &HockeyTeam::getPlayer(const int i) {
    if (i >= roster.size())
        return roster.last();
    return roster[i];
}

HockeyPlayer& HockeyTeam::getPlayerByNumber(const QString num)
{
    for (int i = 0; i < roster.size(); i++) {
        if (roster.at(i).getUni() == num) {
            return roster[i];
        }
    }
    return roster.last();
}

void
HockeyTeam::addPlayer(HockeyPlayer player) {
    roster.append(player);
}

void HockeyTeam::addPeriod(PeriodData pd)
{
    periodData.append(pd);
}

void HockeyTeam::addGame(GameHistory gm)
{
    gameHistory.append(gm);
}

void
HockeyTeam::addPkFail() {
    pkopp++;
    pkoppToday++;
}

HockeyPlayer& HockeyTeam::getGoalie()
{
    return getPlayer(goalie);
}

void HockeyTeam::setGoalie(int index)
{
    if (index >= roster.size()) {
        playerInGoal = false;
    }
    else {
        goalie = index;
        playerInGoal = true;
    }
}

QList<HockeyPlayer> HockeyTeam::getRoster() const
{
    return roster;
}

void HockeyTeam::clearRoster()
{
    roster.clear();
}

void HockeyTeam::clearGameHistory()
{
    gameHistory.clear();
}

void HockeyTeam::clearPeriodData()
{
    periodData.clear();
}

QList<GameHistory> HockeyTeam::getGameHistory() const
{
    return gameHistory;
}

void HockeyTeam::setGameHistory(const QList<GameHistory> &value)
{
    gameHistory = value;
}


QList<PeriodData> HockeyTeam::getPeriodData() const
{
    return periodData;
}
bool HockeyTeam::getPlayerInGoal() const
{
    return playerInGoal;
}

void HockeyTeam::setGoalies(QString goalies)
{
    QString list = goalies;
    int number;
    QString strNum;
    while (list.contains(" ")) {
        strNum = list.left(list.indexOf(" "));
        list = list.mid(list.indexOf(" ")+1);
        number = strNum.toInt();
        for (int i = 0; i < roster.size(); i++) {
            if (number == getPlayer(i).getUni().toInt()) {
                getPlayer(i).setGaavg("Goalie");
                break;
            }
        }
    }
    number = list.toInt();
    for (int i = 0; i < roster.size(); i++) {
        if (number == getPlayer(i).getUni().toInt()) {
            getPlayer(i).setGaavg("Goalie");
            break;
        }
    }
}

double HockeyTeam::getPkPct() const
{
    return (double) pk/pkopp * 100;
}

void HockeyTeam::setPkPct(double value)
{
    pkPct = value;
}

QList<QString> HockeyTeam::getGuiNames()
{
    QList<QString> names;
    for (int i = 0; i < roster.size(); i++) {
        names.append(roster.at(i).getUni() + " - " +
                     roster.at(i).getName());
    }

    return names;
}

double HockeyTeam::getPpPct() const
{
    return (double)ppg/ppopp * 100;
}

void HockeyTeam::setPpPct(double value)
{
    ppPct = value;
}

int HockeyTeam::getPkoppToday() const
{
    return pkoppToday;
}

void HockeyTeam::setPkoppToday(int value)
{
    pkoppToday = value;
}

int HockeyTeam::getPkToday() const
{
    return pkToday;
}

void HockeyTeam::setPkToday(int value)
{
    pkToday = value;
}

int HockeyTeam::getPpoppToday() const
{
    return ppoppToday;
}

void HockeyTeam::setPpoppToday(int value)
{
    ppoppToday = value;
}

int HockeyTeam::getPpgToday() const
{
    return ppgToday;
}

void HockeyTeam::setPpgToday(int value)
{
    ppgToday = value;
}

int HockeyTeam::getPkopp() const
{
    return pkopp;
}

void HockeyTeam::setPkopp(int value)
{
    pkopp = value;
}

int HockeyTeam::getPk() const
{
    return pk;
}

void HockeyTeam::setPk(int value)
{
    pk = value;
}

int HockeyTeam::getPpopp() const
{
    return ppopp;
}

void HockeyTeam::setPpopp(int value)
{
    ppopp = value;
}

int HockeyTeam::getPpg() const
{
    return ppg;
}

void HockeyTeam::setPpg(int value)
{
    ppg = value;
}


void
HockeyTeam::addPkStop() {
    pk++;
    pkopp++;
    pkToday++;
    pkoppToday++;
}

void
HockeyTeam::addPpFail() {
    ppopp++;
    ppoppToday++;
}

void
HockeyTeam::addPpg() {
    ppg++;
    ppopp++;
    ppgToday++;
    ppoppToday++;
}
