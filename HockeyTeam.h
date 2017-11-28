#ifndef HOCKEYTEAM_H
#define HOCKEYTEAM_H

#include <QObject>
#include <QList>
#include "PeriodData.h"
#include "GameHistory.h"
#include "HockeyPlayer.h"
#include <QColor>
#include <QPixmap>

class HockeyTeam : public QObject {
    Q_OBJECT
public:
    HockeyTeam(QString name, QColor color, QPixmap logo);
    HockeyPlayer& getPlayer(const int i);
    HockeyPlayer& getPlayerByNumber(const QString i);
    void addPlayer(HockeyPlayer player);
    void addPeriod(PeriodData pd);
    void addGame(GameHistory gm);
    int getPpg() const;
    void setPpg(int value);

    int getPpopp() const;
    void setPpopp(int value);

    int getPk() const;
    void setPk(int value);

    int getPkopp() const;
    void setPkopp(int value);

    int getPpgToday() const;
    void setPpgToday(int value);

    int getPpoppToday() const;
    void setPpoppToday(int value);

    int getPkToday() const;
    void setPkToday(int value);

    int getPkoppToday() const;
    void setPkoppToday(int value);

    double getPpPct() const;
    void setPpPct(double value);

    double getPkPct() const;
    void setPkPct(double value);

    QList<QString> getGuiNames();

    HockeyPlayer &getGoalie();

    bool getPlayerInGoal() const;

    void setGoalies(QString goalies);

    QList<PeriodData> getPeriodData() const;

    QColor getColor() const;
    void setColor(const QColor &value);

    QPixmap getLogo() const;
    void setLogo(const QPixmap &value);

    QString getName() const;
    void setName(const QString &value);

    QList<GameHistory> getGameHistory() const;
    void setGameHistory(const QList<GameHistory> &value);

    QList<HockeyPlayer> getRoster() const;

    void clearRoster();
    void clearGameHistory();
    void clearPeriodData();

signals:


public slots:
    void addPpg();
    void addPpFail();
    void addPkStop();
    void addPkFail();

    void setGoalie(int index);

private:
    QList<HockeyPlayer> roster;
    int ppg, ppopp, pk, pkopp, timeoutsLeft,
    ppgToday, ppoppToday, pkToday, pkoppToday;
    double ppPct, pkPct;
    bool playerInGoal;

    int goalie;
    QList<PeriodData> periodData;
    QList<GameHistory> gameHistory;

    QColor color;
    QPixmap logo;
    QString name;
    HockeyPlayer dummy;
};

#endif // HOCKEYTEAM_H
