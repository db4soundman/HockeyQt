#include "SetupWizard.h"

SetupWizard::SetupWizard(QString* pAwayFile,
                         QString* pHomeFile, QString* pSponsor,
                         QString* pAwayRank, QString* pHomeRank, QColor* pBg, int* pk, int* pkopp,
                         int* ppg, int* ppopp, QString* goalies, QString* statcrewName,
                         bool *usingTricaster, QString* tricasterIp,
                         int* port, int* hpk, int* hpkopp,int* hppg, int* hppopp) : awayPage(false, pAwayFile, pAwayRank, pk, pkopp, ppg, ppopp),
    homePage(true, pHomeFile, pHomeRank, hpk, hpkopp, hppg, hppopp),
    wizpage(pSponsor, pBg, statcrewName,
            usingTricaster, tricasterIp, port)
    {
    addPage(&awayPage);
    addPage(&homePage);
    addPage(&wizpage);
//    addPage(&ati);
}
