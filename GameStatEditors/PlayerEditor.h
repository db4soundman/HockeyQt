#ifndef PLAYEREDITOR_H
#define PLAYEREDITOR_H

#include <QWidget>
#include <QSpinBox>
#include <QComboBox>
#include "HockeyGame.h"
#include "HockeyPlayer.h"

class PlayerEditor : public QWidget {
    Q_OBJECT
public:
    PlayerEditor(HockeyGame* game, bool homeTeam = false);

public slots:
    void updateSpinBoxes();
    void applyStats();

private slots:
    void changePlayer(int index);

private:
    QSpinBox goalsToday, astToday, penaltiesToday, pimToday;
    QComboBox playerSelect;
    HockeyPlayer* player;
    HockeyTeam* team;

};

#endif // PLAYEREDITOR_H
