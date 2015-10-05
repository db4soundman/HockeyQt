#ifndef PENALTYCONTROL_H
#define PENALTYCONTROL_H

#include <QWidget>
#include "HockeyGame.h"
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
class PenaltyControl : public QWidget {
    Q_OBJECT
public:
    PenaltyControl(HockeyGame* game);

signals:
    void awayPenalty(int length);
    void homePenalty(int length);
    void editPenalties();

public slots:
    void changeUseClock(bool uc);

private slots:
    void awayTwo();
    void awayFour();
    void awayFive();
    void homeTwo();
    void homeFour();
    void homeFive();

private:
    QPushButton ap2, ap4, ap5, hp2, hp4, hp5, show, set, homePenEnd, awayPenEnd;
    QLabel homeLabel, awayLabel;
    QGridLayout *clockLayout, *noClockLayout;
};

#endif // PENALTYCONTROL_H
