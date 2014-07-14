#ifndef HOMESTATCONTROL_H
#define HOMESTATCONTROL_H

#include <QWidget>
#include "HockeyGame.h"
#include <QComboBox>
#include <QPushButton>

class HomeStatControl : public QWidget {
    Q_OBJECT
public:
    HomeStatControl(HockeyGame* game);

signals:
    void requestSeasonLt(int index);
    void requestSeasonSb(int index);
    void requestGameSb(int index);
    void requestGameLt(int index);

private slots:
    void requestSeasonLt();
    void requestGameLt();
    void requestGameSb();
    void requestSeasonSb();

private:
    QComboBox playerSelector;
    QPushButton seasonLt, gameLt, seasonBar, gameBar;
};

#endif // HOMESTATCONTROL_H
