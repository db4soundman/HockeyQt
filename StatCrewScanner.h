#ifndef STATCREWSCANNER_H
#define STATCREWSCANNER_H

#include <QObject>
#include <QTimer>
#include "GameXmlUpdater.h"
#include "HockeyGame.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QThread>
class StatCrewScanner : public QThread
{
    Q_OBJECT
public:
    StatCrewScanner(HockeyGame* game, QString fileName);

public slots:
    void toggleScanner(bool clockStatus);
    void toggleScanner(int pd);
    void toggleScanner();
    void run();
    void toggleEnabled();

signals:
    void statCrewStatus(bool on);

private slots:
    void getStats();
    void updateStats(QNetworkReply *reply);

private:
    GameXmlUpdater* statCrew;
    QTimer* inGame, *breakTime;
    bool isActive, enabled;
    QString statFile;
    QNetworkAccessManager* manager;
};

#endif // STATCREWSCANNER_H
