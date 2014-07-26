#ifndef NCHCSCOREENTRY_H
#define NCHCSCOREENTRY_H

#include <QString>

class NchcScoreEntry {
public:
    NchcScoreEntry(QString pAway = "", QString pHome = "", QString pAwayScore = "",
                   QString pHomeScore = "", QString pTaP = "", bool pConfGame = false);

    QString getAway() const;
    void setAway(const QString& value);

    QString getHome() const;
    void setHome(const QString& value);

    QString getAwayScore() const;
    void setAwayScore(const QString& value);

    QString getHomeScore() const;
    void setHomeScore(const QString& value);

    QString getTimeAndPd() const;
    void setTimeAndPd(const QString& value);

    bool getConfGame() const;
    void setConfGame(bool value);

private:
    QString away, home, awayScore, homeScore, timeAndPd;
    bool confGame;
};

#endif // NCHCSCOREENTRY_H
