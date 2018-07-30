#ifndef SETUPWIZARD_H
#define SETUPWIZARD_H

#include <QWizard>
#include <QPushButton>
#include <QColor>
#include "SetupPage.h"
#include "AwayTeamInfo.h"
#include "TeamSetupPage.h"

class SetupWizard : public QWizard {
public:
    SetupWizard(QString* pAwayFile, QString* pHomeFile,
                QString* pSponsor, QString* pAnnouncer, QString* pAwayRank, QString* pHomeRank,
                QColor* pBg, int* pk, int* pkopp,
                int* ppg, int* ppopp, QString* goalies, QString* statcrewName, bool* usingTricaster,
                QString *tricasterIp, int *port);

private:
    SetupPage wizpage;
    AwayTeamInfo ati;
    TeamSetupPage awayPage, homePage;
};

#endif // SETUPWIZARD_H
