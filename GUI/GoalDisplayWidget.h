#ifndef GOALDISPLAYWIDGET_H
#define GOALDISPLAYWIDGET_H

#include <QWidget>
#include "HockeyGame.h"
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class GoalDisplayWidget : public QWidget {
    Q_OBJECT
public:
    GoalDisplayWidget(HockeyGame* game, bool homeTeam, bool standAlone=true);

signals:
    void showGoalText(int scorer, int a1, int a2);
protected:
    QGridLayout* createLayout();

private slots:
    void prepareToSendSignal();

protected:
    QComboBox scorer, assist1, assist2;
    QLabel shooter, firstAssister, secondAssister;
    QPushButton show;

};

#endif // GOALDISPLAYWIDGET_H
