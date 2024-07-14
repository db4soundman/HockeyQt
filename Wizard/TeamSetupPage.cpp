#include "TeamSetupPage.h"
#include "MiamiAllAccessHockey.h"
#include "School.h"
#include <QGridLayout>
#include <QFileDialog>
#include <QColorDialog>
#include <QStandardPaths>
#include <QTextStream>
#include <QFormLayout>
#include <QMessageBox>
#include "Params.h"


TeamSetupPage::TeamSetupPage(bool home, QString* pAwayFile,
                     QString* pAwayRank, int *pk, int *pkopp, int *ppg, int *ppopp): colorPrev(32,32), isHome(home), logoPrev(50,50), logoBgPrev(32,32) {
    colorPrev.fill(!isHome ? MiamiAllAccessHockey::awaySchool.getPrimaryColor() : MiamiAllAccessHockey::homeSchool.getPrimaryColor());
    logoBgPrev.fill(!isHome? MiamiAllAccessHockey::awaySchool.getPrimaryLogoBg() : MiamiAllAccessHockey::homeSchool.getPrimaryLogoBg());
    logoPrev = !isHome ? MiamiAllAccessHockey::awaySchool.getLogo().scaledToWidth(50) : MiamiAllAccessHockey::homeSchool.getLogo().scaledToWidth(50);
    nameLine.setText(isHome? MiamiAllAccessHockey::homeSchool.getTitle() : MiamiAllAccessHockey::awaySchool.getTitle());
    shortLine.setText(isHome? MiamiAllAccessHockey::homeSchool.getShortName() : MiamiAllAccessHockey::awaySchool.getShortName());
    swatchSelector = new QComboBox();
    swatchSelector->addItem("1");
    swatchSelector->addItem("2");
    colorBox = new QLabel();
    colorBox->setPixmap(colorPrev);
    logoPrevBox.setPixmap(logoBgPrev);
    browseBtn.setText("Stat File");
    chooseColor.setText("Primary Color");
    chooseLogoBg.setText("Logo Background");
    browseLogo.setText("Logo");
    profileDialog.setText("Load Profile");
    logoBox.setPixmap(logoPrev);
    file = pAwayFile;
    rank = pAwayRank;
    pkAddr = pk;
    pkoppAddr = pkopp;
    ppgAddr = ppg;
    ppoppAddr = ppopp;

    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget(new QLabel("Team Name:"), 0, 0);
    mainLayout->addWidget(&nameLine, 0, 1);
    mainLayout->addWidget(&chooseColor, 0, 2);
    mainLayout->addWidget(colorBox,0,3);
    mainLayout->addWidget(new QLabel("Swatch Color:"), 0, 4);
    mainLayout->addWidget(swatchSelector, 0, 5);
    mainLayout->addWidget(&browseBtn, 0, 6);
    mainLayout->addWidget(&browseLogo, 0, 7);
    mainLayout->addWidget(&profileDialog, 0,8);


    mainLayout->addWidget(new QLabel("Team Rank:"), 0, 9);
    mainLayout->addWidget(&rankLine, 0, 10);
    mainLayout->addWidget(new QLabel("Team Short Name:"), 0, 11);
    mainLayout->addWidget(&shortLine, 0, 12);

    mainLayout->addWidget(&logoBox,1,0);

    mainLayout->addWidget(new QLabel("Logo Background:"), 1,1);
    mainLayout->addWidget(&logoPrevBox,1,2);
    mainLayout->addWidget(&chooseLogoBg,1,3);

    pkInput.setMaximum(1000);
    pkoppInput.setMaximum(1000);
    ppgInput.setMaximum(1000);
    ppoppInput.setMaximum(1000);
    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(new QLabel("Pk"), &pkInput);
    formLayout->addRow("Pk Opp", &pkoppInput);
    formLayout->addRow("PP Goals", &ppgInput);
    formLayout->addRow("PP Opp", &ppoppInput);

    mainLayout->addLayout(formLayout,2,0,1,11);

    setLayout(mainLayout);

    connect(&browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
    connect(&chooseColor, SIGNAL(clicked()), this, SLOT(colorDiag()));
    connect(&chooseLogoBg, SIGNAL(clicked()), this, SLOT(logoBgDiag()));
    connect(&browseLogo, SIGNAL(clicked()), this, SLOT(logoBrowse()));
    connect(&profileDialog, SIGNAL(clicked()), this, SLOT(profileBrowse()));
    connect(swatchSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(applyProfile()));
    QString title = !home ? "Away" : "Home";
    title += + " Team Information";
    setTitle(title);
}

bool TeamSetupPage::validatePage()
{
    *rank = rankLine.text();
    if (!isHome) {
        MiamiAllAccessHockey::awaySchool.setFullName(nameLine.text().toUpper());
        MiamiAllAccessHockey::awaySchool.setShortName(shortLine.text().toUpper());
    } else {
        MiamiAllAccessHockey::homeSchool.setFullName(nameLine.text().toUpper());
        MiamiAllAccessHockey::homeSchool.setShortName(shortLine.text().toUpper());
    }
    *ppgAddr = ppgInput.value();
    *ppoppAddr = ppoppInput.value();
    *pkAddr = pkInput.value();
    *pkoppAddr = pkoppInput.value();
    return true;
}

void TeamSetupPage::browse()
{
    QString tfile = QFileDialog::getOpenFileName(0, "File");
    if (!tfile.isEmpty())
        *file = tfile;
}

void TeamSetupPage::colorDiag()
{
    QColor temp = QColorDialog::getColor(MiamiAllAccessHockey::awaySchool.getPrimaryColor(), 0, "Team Color");
    if (temp.isValid()) {
        if (!isHome) {
            MiamiAllAccessHockey::awaySchool.setPrimaryColor(temp);
        } else {
            MiamiAllAccessHockey::homeSchool.setPrimaryColor(temp);
        }
        colorPrev.fill(temp);
        colorBox->setPixmap(colorPrev);
    }
}

void TeamSetupPage::logoBgDiag()
{
    QColor temp = QColorDialog::getColor(MiamiAllAccessHockey::awaySchool.getPrimaryLogoBg(), 0, "Logo Background Color");
    if (temp.isValid()) {
        if (!isHome) {
            MiamiAllAccessHockey::awaySchool.setPrimaryLogoBg(temp);
        } else {
            MiamiAllAccessHockey::homeSchool.setPrimaryLogoBg(temp);
        }
        logoBgPrev.fill(temp);
        logoPrevBox.setPixmap(logoBgPrev);
    }
}

void TeamSetupPage::logoBrowse() {
    QString file = QFileDialog::getOpenFileName(0, "Team Logo");
    if (!file.isEmpty()){
        QPixmap p(file);
        if (isHome) {
            MiamiAllAccessHockey::homeSchool.setLogo(p);
            logoPrev = MiamiAllAccessHockey::homeSchool.getLogo().scaledToWidth(50);
            logoBox.setPixmap(logoPrev);
        } else {
            MiamiAllAccessHockey::awaySchool.setLogo(p);
            logoPrev = MiamiAllAccessHockey::awaySchool.getLogo().scaledToWidth(50);
            logoBox.setPixmap(logoPrev);
        }
    }
}

void TeamSetupPage::profileBrowse() {
    Params params = Params((MiamiAllAccessHockey::getAppDirPath() + "/settings.txt").toStdString());
    QString logoDir = params.isDefined("LOGOS_DIR") ? params.stringValue("LOGOS_DIR") : QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)+"/IMS Images/Logos_Keyable/";
    QString swatchDir = params.isDefined("SWATCH_DIR") ? params.stringValue("SWATCH_DIR") : QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)+"/IMS Images/Swatches/";
    QString file = QFileDialog::getOpenFileName(0, "ESPN Profile",logoDir);
    if (!file.isEmpty()) {
        QString name = file.mid(file.lastIndexOf('/')+1).split('.')[0];
        Profile p("", "", "", "", logoDir + name+".PNG",swatchDir + name + ".PNG");
        activeProfile = p;
        applyProfile();
    }
}


void TeamSetupPage::applyProfile()
{
    if (!activeProfile.getLogoPath().isEmpty()) {
//        nameLine.setText(activeProfile.getFullName());
        QImage swatch(activeProfile.getSwatchPath());
        School s (activeProfile,swatch,QPixmap::fromImage(MiamiAllAccessHockey::getTrimmedLogo(activeProfile.getLogoPath())));
        QColor awayColor;
        switch (swatchSelector->currentIndex()) {
        case 0:
            awayColor = s.getPrimaryColor();
            break;
        default:
            awayColor = s.getSecondaryColor();
        }
        colorPrev.fill(awayColor);
        colorBox->setPixmap(colorPrev);
        logoBgPrev.fill(s.getPrimaryLogoBg());
        logoPrevBox.setPixmap(logoBgPrev);
        if (!isHome) {
            MiamiAllAccessHockey::awaySchool = s;
            logoPrev = MiamiAllAccessHockey::awaySchool.getLogo().scaledToWidth(50);
        }
        else {
            MiamiAllAccessHockey::homeSchool = s;
            logoPrev = MiamiAllAccessHockey::homeSchool.getLogo().scaledToWidth(50);
        }
        logoBox.setPixmap(logoPrev);
//        shortLine.setText(activeProfile.getShortName());
    }
}
