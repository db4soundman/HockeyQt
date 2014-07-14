#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <QWidget>
#include "HockeyGame.h"
#include <QLabel>

class GameInfo : public QWidget{
    Q_OBJECT
public:
    GameInfo(HockeyGame* game);

signals:

public slots:
    void updateTime();
    void updateHomeScore(int score);
    void updateAwayScore(int score);
    void updatePeriod(int newPd);

private:
    QLabel awayTeamName, awayTeamScore, homeTeamName, homeTeamScore, pd, time;
    Clock* clock;

};

#endif // GAMEINFO_H
