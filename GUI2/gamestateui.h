#ifndef GAMESTATEUI_H
#define GAMESTATEUI_H

#include <QObject>
#include <QWidget>
#include "HockeyGame.h"
#include "Goalies.h"
#include <QLabel>

class GameStateUI: public QWidget
{
    Q_OBJECT
public:
    GameStateUI(HockeyGame *game);
    ~GameStateUI();

public slots:
    void updateData(QByteArray data);

private:
    Goalies goalieUi;
    HockeyGame* game;
    QLabel homeScore, awayScore, time, homeP1, awayP1,
    homeP2, awayP2, homeTol, awayTol, awayClock1,
    homeClock1, awayClock2, homeClock2, hSog, aSog;
};

#endif // GAMESTATEUI_H
