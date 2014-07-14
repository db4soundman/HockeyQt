#ifndef SCORECONTROL_H
#define SCORECONTROL_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "HockeyGame.h"

class ScoreControl : public QWidget {
public:
    ScoreControl(HockeyGame* game);

private:
    QLabel title;
    QPushButton ag, hg, am, hm;
};

#endif // SCORECONTROL_H
