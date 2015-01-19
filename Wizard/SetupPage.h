#ifndef SETUPPAGE_H
#define SETUPPAGE_H

#include <QWizardPage>
#include <QPushButton>
#include <QColor>
#include <QLineEdit>
#include <QCheckBox>

class SetupPage : public QWizardPage {
    Q_OBJECT
public:
    SetupPage(QString* pAwayName, QString* pHomeName, QString* pAwayFile, QString* pHomeFile,
              QString* pSponsor, QString* pAnnouncer, QString* pAwayRank, QString* pHomeRank,
              QColor* pAwayColor, QColor* pHomeColor, QColor* pBg, QString* pStatCrew, bool *pUsingTricaster);
    bool validatePage();

private slots:
    void homeBrowse();
    void awayBrowse();
    void statCrewBrowse();
    void awayColorDiag();
    void homeColorDiag();
    void bgDiag();

private:
    QString* awayName, *homeName, *awayRank, *homeRank, *homeFile, *awayFile, *sponsor, *announcer, *statCrew;
    QColor* awayColor, *homeColor,  *bg;
    QPushButton browseAway, browseHome, chooseHColor, chooseAColor, chooseBg, browseStatCrew;
    QLineEdit homeNameLine, awayNameLine, awayRankLine, homeRankLine, sponsorLine, announcerLine;
    QCheckBox* tricasterBox;
    bool* usingTricaster;
};

#endif // SETUPPAGE_H
