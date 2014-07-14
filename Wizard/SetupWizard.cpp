#include "SetupWizard.h"

SetupWizard::SetupWizard(QString* pAwayName, QString* pHomeName, QString* pAwayFile,
                         QString* pHomeFile, QString* pSponsor, QString* pAnnouncer,
                         QString* pAwayRank, QString* pHomeRank, QColor* pAwayColor,
                         QColor* pHomeColor, QColor* pBg) :
    wizpage(pAwayName, pHomeName, pAwayFile, pHomeFile, pSponsor, pAnnouncer,
            pAwayRank, pHomeRank, pAwayColor, pHomeColor, pBg) {
    addPage(&wizpage);
}
