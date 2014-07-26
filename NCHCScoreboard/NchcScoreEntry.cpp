#include "NchcScoreEntry.h"

NchcScoreEntry::NchcScoreEntry(QString pAway, QString pHome, QString pAwayScore,
                               QString pHomeScore, QString pTaP, bool pConfGame) :
    away(pAway), home(pHome), awayScore(pAwayScore), homeScore(pHomeScore),
    timeAndPd(pTaP), confGame(pConfGame) {
}
QString NchcScoreEntry::getAway() const
{
    return away;
}

void NchcScoreEntry::setAway(const QString& value)
{
    away = value;
}
QString NchcScoreEntry::getHome() const
{
    return home;
}

void NchcScoreEntry::setHome(const QString& value)
{
    home = value;
}
QString NchcScoreEntry::getAwayScore() const
{
    return awayScore;
}

void NchcScoreEntry::setAwayScore(const QString& value)
{
    awayScore = value;
}
QString NchcScoreEntry::getHomeScore() const
{
    return homeScore;
}

void NchcScoreEntry::setHomeScore(const QString& value)
{
    homeScore = value;
}
QString NchcScoreEntry::getTimeAndPd() const
{
    return timeAndPd;
}

void NchcScoreEntry::setTimeAndPd(const QString& value)
{
    timeAndPd = value;
}
bool NchcScoreEntry::getConfGame() const
{
    return confGame;
}

void NchcScoreEntry::setConfGame(bool value)
{
    confGame = value;
}






