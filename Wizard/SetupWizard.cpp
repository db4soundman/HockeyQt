#include "SetupWizard.h"

SetupWizard::SetupWizard(QString* pAwayFile,
                         QString* pHomeFile, QString* pSponsor,
                         QString* pAwayRank, QString* pHomeRank, QColor* pBg, int* pk, int* pkopp,
                         int* ppg, int* ppopp, QString* goalies, QString* statcrewName,
                         bool *usingTricaster, QString* tricasterIp,
                         int* port) : awayPage(false, pAwayFile, pAwayRank), homePage(true, pHomeFile, pHomeRank),
    wizpage(pSponsor, pBg, statcrewName,
            usingTricaster, tricasterIp, port),
    ati (pk, pkopp, ppg, ppopp, goalies){
    addPage(&awayPage);
    addPage(&homePage);
    addPage(&wizpage);
    addPage(&ati);
}
