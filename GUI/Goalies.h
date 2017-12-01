#ifndef GOALIES_H
#define GOALIES_H

#include <QWidget>
#include "HockeyGame.h"
#include <QComboBox>
#include <QPushButton>

class Goalies : public QWidget {
    Q_OBJECT
public:
    Goalies(HockeyGame* game);

signals:
    void requestHomeLt(int player, bool home);
    void requestAwayLt(int player, bool home);
    void requestHomeSb(int player, bool home);
    void requestAwaySb(int player, bool home);
    void requestHomeSeason(int player, bool home);
    void requestAwaySeason(int player, bool home);

private slots:
    void getHomeLt();
    void getAwayLt();
    void getHomeSb();
    void getAwaySb();
    void getAwaySeason();
    void getHomeSeason();
    void updateAwayRoster();
    void updateHomeRoster();

private:
    QComboBox homeGoalie, awayGoalie;
    QPushButton awayLt, awaySB, homeLt, homeSB, awaySeason, homeSeason;
    HockeyGame* game;

};

#endif // GOALIES_H
