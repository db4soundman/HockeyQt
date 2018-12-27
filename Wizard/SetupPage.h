#ifndef SETUPPAGE_H
#define SETUPPAGE_H

#include <QWizardPage>
#include <QPushButton>
#include <QColor>
#include <QLineEdit>
#include <QCheckBox>
#include <QPixmap>
#include <QLabel>
#include <QComboBox>
#include "Profile.h"
class SetupPage : public QWizardPage {
    Q_OBJECT
public:
    SetupPage(QString* pSponsor,
              QColor* pBg, QString* pStatCrew, bool *pUsingTricaster,
              QString *tricasterIp, int* portNum);
    bool validatePage();

private slots:
    void statCrewBrowse();
    void bgDiag();
    void showHelp();

private:
    QString *sponsor, *statCrew, *tricasterIp;
    QColor *bg;
    QPushButton chooseBg, browseStatCrew, ipHelp;
    QLineEdit sponsorLine, announcer1,announcer2,announcer3,twitter1,twitter2,twitter3, hashtag, tricasterIpLine;
    QCheckBox* tricasterBox;
    QComboBox* portSelector;
    bool* usingTricaster;
    //ProfileWidget profileSelector;
    int *port;
};

#endif // SETUPPAGE_H
