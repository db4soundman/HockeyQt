#ifndef GOALPOPUI_H
#define GOALPOPUI_H

#include <QObject>
#include "GoalDisplayWidget.h"

class GoalPopUI : public GoalDisplayWidget
{
    Q_OBJECT
public:
    GoalPopUI(HockeyGame* game, bool homeTeam);

private slots:
    void updatePreview();

private:

    QLabel previewText;
    HockeyGame* game;
    bool homeTeam;
};

#endif // GOALPOPUI_H
