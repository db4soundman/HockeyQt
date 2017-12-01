#ifndef STATPOPUI_H
#define STATPOPUI_H

#include <QObject>
#include "HomeStatControl.h"
#include <QLabel>

class StatPopUI : public HomeStatControl
{
    Q_OBJECT
public:
    StatPopUI(HockeyGame* game, bool phome);

public slots:
    void updateSeasonPreview();
    void updateGamePreview();
    void updateRoster();

private:
    HockeyGame* game;
    QLabel seasonPreview, gamePreview;
};

#endif // STATPOPUI_H
