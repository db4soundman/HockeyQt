#ifndef TEAMSETUPPAGE_H
#define TEAMSETUPPAGE_H

#include <QWizardPage>
#include <QPushButton>
#include <QColor>
#include <QLineEdit>
#include <QCheckBox>
#include <QPixmap>
#include <QLabel>
#include <QComboBox>
#include "Profile.h"
class TeamSetupPage: public QWizardPage {
    Q_OBJECT
public:
    TeamSetupPage(bool home, QString* pAwayFile,
                  QString* pAwayRank);
    bool validatePage();

private slots:
    void browse();
    void colorDiag();
    void logoBrowse();
    void applyProfile();
    void profileBrowse();

private:
    QString *rank, *file;
    QPushButton browseBtn,chooseColor, browseLogo, profileDialog;
    QLineEdit nameLine, rankLine, shortLine;
    QPixmap colorPrev, logoPrev;
    QComboBox* swatchSelector;
    QLabel *colorBox, logoBox;
    Profile activeProfile;
    bool isHome;
};

#endif // TEAMSETUPPAGE_H
