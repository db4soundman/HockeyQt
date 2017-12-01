#ifndef PENALTYDISPLAY_H
#define PENALTYDISPLAY_H

#include <QWidget>
#include "HockeyGame.h"
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include "HockeyTeam.h"

class PenaltyDisplay : public QWidget {
    Q_OBJECT
public:
    PenaltyDisplay(HockeyGame* game, bool homeTeam, bool standAlone=true);

    QHBoxLayout * createLayout();

signals:
    void callForPenaltyText(int player, QString penalty);

protected slots:
    void prepareSignal();
    void updateRoster();

protected:
    QComboBox penaltySelector, playerSelector;
    QPushButton show;
    HockeyTeam* team;
};

#endif // PENALTYDISPLAY_H
