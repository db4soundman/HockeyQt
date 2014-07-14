#ifndef GOALDISPLAYWIDGET_H
#define GOALDISPLAYWIDGET_H

#include <QWidget>
#include "HockeyGame.h"
#include <QComboBox>
#include <QLabel>
#include <QPushButton>

class GoalDisplayWidget : public QWidget {
    Q_OBJECT
public:
    GoalDisplayWidget(HockeyGame* game, bool homeTeam);

signals:
    void showGoalText(int scorer, int a1, int a2);
private slots:
    void prepareToSendSignal();

private:
    QComboBox scorer, assist1, assist2;
    QLabel shooter, firstAssister, secondAssister;
    QPushButton show;

};

#endif // GOALDISPLAYWIDGET_H
