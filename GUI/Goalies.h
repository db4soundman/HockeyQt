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
    void requestHomeLt(int player);
    void requestAwayLt(int player);
    void requestHomeSb(int player);
    void requestAwaySb(int player);

private slots:
    void getHomeLt();
    void getAwayLt();
    void getHomeSb();
    void getAwaySb();

private:
    QComboBox homeGoalie, awayGoalie;
    QPushButton awayLt, awaySB, homeLt, homeSB;

};

#endif // GOALIES_H
