#ifndef SOGCONTROL_H
#define SOGCONTROL_H

#include <QGroupBox>
#include "HockeyGame.h"
#include <QPushButton>
#include <QLabel>

class SogControl : public QGroupBox {
    Q_OBJECT
public:
    SogControl(HockeyGame* game);

signals:
    void showSOG(QString sog);

public slots:
    void updateHomeSog(int sog);
    void updateAwaySog(int sog);
    void callSogDisplay();
private:
    QLabel homeLabel, awayLabel;
    QString homeName, awayName;
    QPushButton hp1, ap1, hm1, am1, show;


};

#endif // SOGCONTROL_H
