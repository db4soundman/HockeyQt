#ifndef GAMESTATEUI_H
#define GAMESTATEUI_H

#include <QObject>
#include <QWidget>
#include "HockeyGame.h"
#include "Goalies.h"
#include <QLabel>

class GameStateUI: public QWidget
{
public:
    GameStateUI(HockeyGame *game);
    ~GameStateUI();

public slots:
    void updateData();

private:
    Goalies goalieUi;
    HockeyGame* game;
    QLabel homeScore, awayScore, time, homeP1, awayP1,
    homeP2, awayP2, homeTol, awayTol, awayClock1,
    homeClock1, awayClock2, homeClock2;
};

#endif // GAMESTATEUI_H
