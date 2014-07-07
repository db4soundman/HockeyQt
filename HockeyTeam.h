#ifndef HOCKEYTEAM_H
#define HOCKEYTEAM_H

#include <QObject>
#include <QList>
#include "HockeyPlayer.h"

class HockeyTeam : public QObject {
    Q_OBJECT
public:
    HockeyTeam();
    const HockeyPlayer& getPlayer(const int i);
    void addPlayer(const HockeyPlayer player);
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

signals:


public slots:
    void addPpg();
    void addPpFail();
    void addPkStop();
    void addPkFail();


private:
    QList<HockeyPlayer> roster;
    int ppg, ppopp, pk, pkopp,
    ppgToday, ppoppToday, pkToday, pkoppToday;
    double ppPct, pkPct;
    // period data???
    // game history???
};

#endif // HOCKEYTEAM_H
