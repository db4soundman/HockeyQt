#ifndef FACEOFFCONTROL_H
#define FACEOFFCONTROL_H

#include <QObject>
#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include "HockeyGame.h"

class FaceoffControl : public QWidget
{
    Q_OBJECT
public:
    FaceoffControl(HockeyGame* game, bool standAlone=true, QWidget *parent = 0);

    QGridLayout * getLayout();

signals:
    void showFaceoffComp(int awayWins, int homeWins);

private slots:
    void requestGraphic();

protected:
    QSpinBox awayFaceoffWins, homeFaceoffWins;
    QPushButton show;
    QLabel awayLabel, homeLabel;
};


#endif // FACEOFFCONTROL_H
