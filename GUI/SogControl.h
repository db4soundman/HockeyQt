#ifndef SOGCONTROL_H
#define SOGCONTROL_H

#include <QGroupBox>
#include "HockeyGame.h"
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

class SogControl : public QGroupBox {
    Q_OBJECT
public:
    SogControl(HockeyGame* game, bool standAlone=true);

    QGridLayout * getLayout();

signals:
    void showSOG(QString sog);

public slots:
    void updateHomeSog(int sog);
    void updateAwaySog(int sog);
    void callSogDisplay();
    void disableButtons();
    void enableButtons();
protected:
    QLabel homeLabel, awayLabel;
    QString homeName, awayName;
    QPushButton hp1, ap1, hm1, am1, showTopBar, showLt;


};

#endif // SOGCONTROL_H
