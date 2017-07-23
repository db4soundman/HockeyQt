#ifndef PENALTYDISPLAY_H
#define PENALTYDISPLAY_H

#include <QWidget>
#include "HockeyGame.h"
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>

class PenaltyDisplay : public QWidget {
    Q_OBJECT
public:
    PenaltyDisplay(HockeyGame* game, bool homeTeam, bool standAlone=true);

    QHBoxLayout * createLayout();

signals:
    void callForPenaltyText(int player, QString penalty);

private slots:
    void prepareSignal();

protected:
    QComboBox penaltySelector, playerSelector;
    QPushButton show;
};

#endif // PENALTYDISPLAY_H
