#ifndef STATCREWSCANNER_H
#define STATCREWSCANNER_H

#include <QObject>
#include <QTimer>
#include "GameXmlUpdater.h"
#include "HockeyGame.h"
class StatCrewScanner : public QObject
{
public:
    StatCrewScanner(HockeyGame* game, QString fileName);

public slots:
    void toggleScanner(int pd);
    void toggleScanner();

private slots:
    void updateStats();

private:
    GameXmlUpdater* statCrew;
    QTimer* trigger;
    bool isActive;
};

#endif // STATCREWSCANNER_H
