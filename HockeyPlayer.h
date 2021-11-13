#ifndef HOCKEYPLAYER_H
#define HOCKEYPLAYER_H

#include <QObject>

class HockeyPlayer : public QObject {
    Q_OBJECT
public:
    HockeyPlayer();
    HockeyPlayer(const HockeyPlayer& p);
    HockeyPlayer& operator = (const HockeyPlayer& p);
    bool operator< (HockeyPlayer& rhs);

    QString getName() const;
    void setName(const QString& value);

    QString getUni() const;
    void setUni(const QString& value);

    QString getYear() const;
    void setYear(const QString& value);

    QString getPlusMinus() const;
    void setPlusMinus(const QString& value);

    int getGp() const;
    void setGp(int value);

    int getGoals() const;
    void setGoals(int value);

    int getAssists() const;
    void setAssists(int value);

    int getPts() const;
    void setPts(int value);

    int getPenalties() const;
    void setPenalties(int value);

    int getPim() const;
    void setPim(int value);

    int getGa() const;
    void setGa(int value);

    int getSaves() const;
    void setSaves(int value);

    int getShotsFaced() const;
    void setShotsFaced(int value);

    int getWins() const;
    void setWins(int value);

    int getLosses() const;
    void setLosses(int value);

    int getGoalsToday() const;
    void setGoalsToday(int value);

    int getAssistsToday() const;
    void setAssistsToday(int value);

    int getPtsToday() const;
    void setPtsToday(int value);

    int getPenaltiesToday() const;
    void setPenaltiesToday(int value);

    int getPimToday() const;
    void setPimToday(int value);

    int getGaToday() const;
    void setGaToday(int value);

    int getSavesToday() const;
    void setSavesToday(int value);

    int getShotsFacedToday() const;
    void setShotsFacedToday(int value);

    QString getGaavg() const;
    void setGaavg(const QString& value);

    void addSave();
    void minusSave();
    void addGa();
    void minusGa();

    double getSvPct();
    void calcSvPct();

private:
    QString name, uni, year, plusMinus, gaavg;
    int gp, goals, assists, pts, penalties, pim;
    // Goalie stats
    int ga, saves, shotsFaced, wins, losses;

    int goalsToday, assistsToday, ptsToday, penaltiesToday,
    pimToday, gaToday, savesToday, shotsFacedToday;
    double svPct;
};

#endif // HOCKEYPLAYER_H
