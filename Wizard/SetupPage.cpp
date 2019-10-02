#include "SetupPage.h"
#include "MiamiAllAccessHockey.h"
#include "School.h"
#include <QGridLayout>
#include <QFileDialog>
#include <QColorDialog>
#include <QStandardPaths>
#include <QTextStream>
#include <QMessageBox>
#include "globals.h"
#include "Params.h"

SetupPage::SetupPage(QString* pSponsor, QColor* pBg, QString* pStatCrew,
                     bool *pUsingTricaster, QString* tricasterIp, int *portNum) {
    chooseBg.setText("Background Color");
    browseStatCrew.setText("GameFile");
    ipHelp.setText("How do I determine this?");
    sponsor = (pSponsor);
    statCrew = pStatCrew;
    bg = pBg;
    usingTricaster = pUsingTricaster;
    this->tricasterIp = tricasterIp;
    port = portNum;
    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget(&chooseBg, 4, 0);
    sponsorLine.setText(*sponsor);
//    mainLayout->addWidget(new QLabel("Sponsor:"), 5, 0);
//    mainLayout->addWidget(&sponsorLine, 5, 1);
    mainLayout->addWidget(new QLabel("Announcer 1(pxp)"), 6, 0);
    mainLayout->addWidget(&announcer1, 6, 1);
    mainLayout->addWidget(new QLabel("Announcer 2(color)"), 7, 0);
    mainLayout->addWidget(&announcer2, 7, 1);
    mainLayout->addWidget(new QLabel("Announcer 3"), 8, 0);
    mainLayout->addWidget(&announcer3, 8, 1);
    mainLayout->addWidget(new QLabel("Twitter 1"), 6, 2);
    mainLayout->addWidget(&twitter1, 6, 3);
    mainLayout->addWidget(new QLabel("Twitter 2"), 7, 2);
    mainLayout->addWidget(&twitter2, 7, 3);
    mainLayout->addWidget(new QLabel("Twitter 3"), 8, 2);
    mainLayout->addWidget(&twitter3, 8, 3);
    tricasterBox = new QCheckBox("Using Tricaster");
    tricasterBox->setChecked(true);
    mainLayout->addWidget(tricasterBox, 9, 0);
    tricasterIpLine.setText(*tricasterIp);
    mainLayout->addWidget(&tricasterIpLine, 9, 1);
    mainLayout->addWidget(&ipHelp,9, 2);
    mainLayout->addWidget(new QLabel("Net Input"),9, 3);
    portSelector = new QComboBox();
    mainLayout->addWidget(portSelector,9, 4);

    portSelector->addItem("1");
    portSelector->addItem("2");

    setLayout(mainLayout);

    connect(&chooseBg, SIGNAL(clicked()), this, SLOT(bgDiag()));
    connect(&browseStatCrew, SIGNAL(clicked()), this, SLOT(statCrewBrowse()));
    connect(&ipHelp, SIGNAL(clicked()), this, SLOT(showHelp()));

    setTitle("Game Information");
    Params p((MiamiAllAccessHockey::getAppDirPath() + "/settings.txt").toStdString());
    announcer1.setText(p.stringValue("ANNOUNCER1"));
    announcer2.setText(p.stringValue("ANNOUNCER2"));
    twitter1.setText(p.stringValue("ANNOUNCER1_TWITTER"));
    twitter2.setText(p.stringValue("ANNOUNCER2_TWITTER"));
}

bool SetupPage::validatePage()
{
    *sponsor = sponsorLine.text();
    Globals::announcer1 = announcer1.text().trimmed();
    Globals::announcer2 = announcer2.text().trimmed();
    Globals::announcer3 = announcer3.text().trimmed();
    Globals::twitter1 = twitter1.text().trimmed().length() > 0 ? (twitter1.text().startsWith("@") ? twitter1.text().trimmed() : "@" + twitter1.text().trimmed()) : "@TheNCHC";
    Globals::twitter2 = twitter2.text().trimmed().trimmed().length() > 0 ? (twitter2.text().startsWith("@") ? twitter2.text().trimmed() : "@" + twitter2.text().trimmed()) : "@TheNCHC";
    Globals::twitter3 = twitter3.text().trimmed().trimmed().length() > 0 ? (twitter3.text().startsWith("@") ? twitter3.text().trimmed() : "@" + twitter3.text().trimmed()) : "@TheNCHC";
    *usingTricaster = tricasterBox->isChecked();
    *tricasterIp = tricasterIpLine.text();
    *port = portSelector->currentIndex() + 7000;
    return true;
}

void SetupPage::statCrewBrowse()
{
    QString file = QFileDialog::getOpenFileName(0, "StatCrew Game File");
    if (!file.isEmpty())
        *statCrew = file;
}

void SetupPage::bgDiag()
{
    QColor temp = QColorDialog::getColor(*bg, 0, "Background Color");
    if (temp.isValid())
        *bg = temp;
}

void SetupPage::showHelp()
{
    QMessageBox msg;
    msg.setText("Exit to Windows on the Tricaster. Open the start menu and type 'cmd' and press enter. "
                "When the command prompt opens, type 'ipconfig'."
                " Scroll to the top and find the 'IPv4 Address...' line under the wireless section.");
    msg.exec();
}
