#ifndef VISITINGGAMESTATCONTROL_H
#define VISITINGGAMESTATCONTROL_H

#include <QWidget>
#include "HockeyGame.h"
#include <QComboBox>
#include <QPushButton>

class VisitingGameStatControl : public QWidget {
    Q_OBJECT
public:
    VisitingGameStatControl(HockeyGame* game);

signals:
    void requestLt(int index);
    void requestSb(int index);

private slots:
    void requestLt();
    void requestSb();

private:
    QComboBox playerSelector;
    QPushButton displayLt, displayBar;
};

#endif // VISITINGGAMESTATCONTROL_H
