#include "HockeyTeam.h"

HockeyTeam::HockeyTeam() {
    ppgToday = ppoppToday = pkToday = pkoppToday = 0;

}

HockeyPlayer* HockeyTeam::getPlayer(const int i) {
    if (i > roster.size())
        return NULL;
    return roster.at(i);
}

void
HockeyTeam::addPlayer(HockeyPlayer* player) {
    roster.append(player);
}

void
HockeyTeam::addPkFail() {
    pkopp++;
    pkoppToday++;
}

HockeyPlayer* HockeyTeam::getGoalie()
{
    return goalie;
}

void HockeyTeam::setGoalie(int index)
{
    if (index >= roster.size()) {
        playerInGoal = false;
    }
    else {
        goalie = getPlayer(index);
        playerInGoal = true;
    }
}
bool HockeyTeam::getPlayerInGoal() const
{
    return playerInGoal;
}

void HockeyTeam::setGoalies(QString goalies)
{
    int number;
    QString strNum;
    while (goalies.contains(" ")) {
        strNum = goalies.left(goalies.indexOf(" ") - 1);
        goalies.mid(goalies.indexOf(" ")+1);
        number = strNum.toInt();
        for (int i = 0; i < roster.size(); i++) {
            if (number == getPlayer(i)->getUni().toInt()) {
                getPlayer(i)->setGaavg("Goalie");
                break;
            }
        }
    }
    number = goalies.toInt();
    for (int i = 0; i < roster.size(); i++) {
        if (number == getPlayer(i)->getUni().toInt()) {
            getPlayer(i)->setGaavg("Goalie");
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
        names.append(roster.at(i)->getUni() + " - " +
                     roster.at(i)->getName());
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
