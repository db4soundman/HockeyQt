#ifndef HOMESTATCONTROL_H
#define HOMESTATCONTROL_H

#include <QWidget>
#include "HockeyGame.h"
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include "HockeyTeam.h"
class HomeStatControl : public QWidget {
    Q_OBJECT
public:
    HomeStatControl(HockeyGame* game, bool phome, bool standAlone=true);

    QHBoxLayout * getFullLayout();

signals:
    void requestSeasonLt(int index, bool home);
    void requestSeasonSb(int index, bool home);
    void requestGameSb(int index, bool home);
    void requestGameLt(int index, bool home);

protected:
    QHBoxLayout* getPopLayout();
    QHBoxLayout* getLowerThirdLayout();

protected slots:
    void requestSeasonLt();
    void requestGameLt();
    void requestGameSb();
    void requestSeasonSb();
    void updateRoster();

protected:
    QComboBox playerSelector;
    QPushButton seasonLt, gameLt, seasonBar, gameBar;
    bool home;
    HockeyTeam* team;
};

#endif // HOMESTATCONTROL_H
