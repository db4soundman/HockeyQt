#ifndef POPUI_H
#define POPUI_H
#include <QObject>
#include <QWidget>
#include "GoalPopUI.h"
#include "PenaltyPopUI.h"
#include "StatPopUI.h"
#include "HockeyGame.h"

class PopUI : public QWidget
{

public:
    PopUI(HockeyGame* game, bool home, QWidget *parent = nullptr);

private:
    GoalPopUI goalPopUi;
    PenaltyPopUI penaltyPopUi;
    StatPopUI statPopUi;
};

#endif // POPUI_H
