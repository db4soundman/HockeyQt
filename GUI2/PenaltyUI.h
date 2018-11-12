#ifndef PENALTYUI_H
#define PENALTYUI_H

#include <QObject>
#include <QWidget>
#include "GoalPopUI.h"
#include "PenaltyPopUI.h"
#include "PpCompUI.h"
#include "StatPopUI.h"
#include "HockeyGame.h"

class PenaltyUI: public QWidget
{
public:
    PenaltyUI(HockeyGame* game, bool home, QWidget *parent = nullptr);

private:
    PenaltyPopUI penaltyUi;
    PpCompUI compUi;
};

#endif // PENALTYUI_H
