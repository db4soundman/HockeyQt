#include "GameHistory.h"

GameHistory::GameHistory(QString opp, QString tScore, QString oScore, QString pds, QString date, QString homeAway)
{
    opponent = opp;
    theirScore = tScore;
    ourScore = oScore;
    this->date = date;
    home = homeAway == "H";
    int numPds = pds.toInt();
    if (numPds == 3) {
        periods = "F";
    } else if (numPds == 4) {
        periods = "F/OT";
    } else if (numPds == 5) {
        periods = "F/2OT";
    } else if (numPds == 6) {
        periods = "F/SO";
    } else {
        periods = "";
    }
}

QString GameHistory::getOpponent() const
{
    return opponent;
}

void GameHistory::setOpponent(const QString &value)
{
    opponent = value;
}

QString GameHistory::getTheirScore() const
{
    return theirScore;
}

void GameHistory::setTheirScore(const QString &value)
{
    theirScore = value;
}

QString GameHistory::getOurScore() const
{
    return ourScore;
}

void GameHistory::setOurScore(const QString &value)
{
    ourScore = value;
}

QString GameHistory::getDate() const
{
    return date;
}

void GameHistory::setDate(const QString &value)
{
    date = value;
}

QString GameHistory::getPeriods() const
{
    return periods;
}

void GameHistory::setPeriods(const QString &value)
{
    periods = value;
}

bool GameHistory::getHome() const
{
    return home;
}

void GameHistory::setHome(bool value)
{
    home = value;
}
