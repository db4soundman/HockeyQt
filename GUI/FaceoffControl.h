#ifndef FACEOFFCONTROL_H
#define FACEOFFCONTROL_H

#include <QObject>
#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include "HockeyGame.h"

class FaceoffControl : public QWidget
{
    Q_OBJECT
public:
    FaceoffControl(HockeyGame* game, QWidget *parent = 0);

signals:
    void showFaceoffComp(int awayWins, int homeWins);

private slots:
    void requestGraphic();

private:
    QSpinBox awayFaceoffWins, homeFaceoffWins;
    QPushButton show;
    QLabel awayLabel, homeLabel;
};


#endif // FACEOFFCONTROL_H
