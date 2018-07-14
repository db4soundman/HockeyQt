#include "SetupWizard.h"

SetupWizard::SetupWizard(QString* pAwayFile,
                         QString* pHomeFile, QString* pSponsor, QString* pAnnouncer,
                         QString* pAwayRank, QString* pHomeRank, QColor* pBg, int* pk, int* pkopp,
                         int* ppg, int* ppopp, QString* goalies, QString* statcrewName,
                         bool *usingTricaster, QString* tricasterIp,
                         int* port) :
    wizpage(pAwayFile, pHomeFile, pSponsor, pAnnouncer,
            pAwayRank, pHomeRank, pBg, statcrewName,
            usingTricaster, tricasterIp, port),
    ati (pk, pkopp, ppg, ppopp, goalies){
    addPage(&wizpage);
    addPage(&ati);
}
