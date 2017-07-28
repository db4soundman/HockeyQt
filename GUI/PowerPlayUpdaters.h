#ifndef POWERPLAYUPDATERS_H
#define POWERPLAYUPDATERS_H

#include <QWidget>
#include "HockeyGame.h"
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

class PowerPlayUpdaters : public QWidget {
    Q_OBJECT
public:
    PowerPlayUpdaters(HockeyGame* game, bool standAlone=true);

    QGridLayout * getLayout();

protected:
    QPushButton awayGoal, awayFail, homeGoal, homeFail, show;
    QLabel awayLabel, homeLabel;
};

#endif // POWERPLAYUPDATERS_H
