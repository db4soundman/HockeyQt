#include "SetupWizard.h"

SetupWizard::SetupWizard(QString* pAwayName, QString* pHomeName, QString* pAwayFile,
                         QString* pHomeFile, QString* pSponsor, QString* pAnnouncer,
                         QString* pAwayRank, QString* pHomeRank, QColor* pAwayColor,
                         QColor* pHomeColor, QColor* pBg, int* pk, int* pkopp,
                         int* ppg, int* ppopp, QString* goalies, QString* statcrewName, bool *usingTricaster) :
    wizpage(pAwayName, pHomeName, pAwayFile, pHomeFile, pSponsor, pAnnouncer,
            pAwayRank, pHomeRank, pAwayColor, pHomeColor, pBg, statcrewName, usingTricaster),
    ati (pk, pkopp, ppg, ppopp, goalies){
    addPage(&wizpage);
    addPage(&ati);
}
