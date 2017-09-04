#ifndef CGSIMULATOR_H
#define CGSIMULATOR_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QTimer>
#include <QPushButton>
#include "Clock.h"

class CGSimulator : public QWidget
{
    Q_OBJECT
public:
    CGSimulator(QWidget *parent = 0);
    void sendCgConnected();

signals:
    void dataReceived(QByteArray data);
    void serialConnected();

public slots:

    void handleTimeout();

private slots:
    void clockEdited();
    void h1Edited();
    void h2Edited();
    void a1Edited();
    void a2Edited();

    void h1Expired();
    void h2Expired();
    void a1Expired();
    void a2Expired();

    void startClicked();
    void stopClicked();

private:
    QLineEdit homeScore, awayScore, time, homeP1, awayP1,
    homeP2, awayP2, homeTol, awayTol, awayClock1,
    homeClock1, awayClock2, homeClock2, hSog, aSog;
    QCheckBox clockStopped;
    QTimer timer;
    QPushButton start, stop;
    Clock gameClock, h1,h2,a1,a2;
    bool clockHasChanged, h1HasChanged, h2HasChanged, a1HasChanged, a2HasChanged;
};

#endif // CGSIMULATOR_H
