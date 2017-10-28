#ifndef GAMEHISTORY_H
#define GAMEHISTORY_H

#include <QObject>
class GameHistory
{
public:
    GameHistory(QString opp, QString tScore, QString oScore, QString pds, QString date, QString homeAway);

    QString getOpponent() const;
    void setOpponent(const QString &value);

    QString getTheirScore() const;
    void setTheirScore(const QString &value);

    QString getOurScore() const;
    void setOurScore(const QString &value);

    QString getDate() const;
    void setDate(const QString &value);

    QString getPeriods() const;
    void setPeriods(const QString &value);

    bool getHome() const;
    void setHome(bool value);

private:
    QString opponent, theirScore, ourScore, date, periods;
    bool home;
};

#endif // GAMEHISTORY_H
