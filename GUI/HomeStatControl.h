#ifndef HOMESTATCONTROL_H
#define HOMESTATCONTROL_H

#include <QWidget>
#include "HockeyGame.h"
#include <QComboBox>
#include <QPushButton>

class HomeStatControl : public QWidget {
    Q_OBJECT
public:
    HomeStatControl(HockeyGame* game, bool phome);

signals:
    void requestSeasonLt(int index, bool home);
    void requestSeasonSb(int index, bool home);
    void requestGameSb(int index, bool home);
    void requestGameLt(int index, bool home);

private slots:
    void requestSeasonLt();
    void requestGameLt();
    void requestGameSb();
    void requestSeasonSb();

private:
    QComboBox playerSelector;
    QPushButton seasonLt, gameLt, seasonBar, gameBar;
    bool home;
};

#endif // HOMESTATCONTROL_H
