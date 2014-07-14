#ifndef POWERPLAYUPDATERS_H
#define POWERPLAYUPDATERS_H

#include <QWidget>
#include "HockeyGame.h"
#include <QPushButton>
#include <QLabel>

class PowerPlayUpdaters : public QWidget {
    Q_OBJECT
public:
    PowerPlayUpdaters(HockeyGame* game);

private:
    QPushButton awayGoal, awayFail, homeGoal, homeFail, show;
    QLabel awayLabel, homeLabel;
};

#endif // POWERPLAYUPDATERS_H
