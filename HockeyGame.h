#ifndef HOCKEYGAME_H
#define HOCKEYGAME_H

#include <QObject>
#include "Clock.h"
#include <QString>
#include <QTimer>

class HockeyGame : public QObject {
    Q_OBJECT
public:
    HockeyGame(QString awayName, QString homeName);

public slots:
    void homeGoal();
    void awayGoal();
    void homeLoseGoal();
    void awayLoseGoal();
    void advancePeriod();
    void rewindPeriod();
    void addHomePenalty(int time);
    void addAwayPenalty(int time);
    void homePenaltyExpired();
    void awayPenaltyExpired();
    void toggleClock();
    void addHomeSOG();
    void addAwaySOG();
    void subHomeSOG();
    void subAwaySOG();

signals:
    void homeScoreChanged(int score);
    void awayScoreChanged(int score);
    void periodChanged(int pd);
    void penaltyChanged(int pos, Clock* clock, QString description);
    void clockIsRunning(bool isRunning);
    void awaySogChanged(int sog);
    void homeSogChanged(int sog);


private:
    QString homeName, awayName;
    int awayScore, homeScore, period, homeSOG, awaySOG;
    Clock gameClock;
    QList<Clock*> awayPenalty, homePenalty;
    QTimer timer;
    bool clockRunning;
    // Teams
    // GUI is separate class
    // GraphicsVars

    void determinePpClockForScoreboard();
    Clock* getLowestPpClock();
};

#endif // HOCKEYGAME_H
