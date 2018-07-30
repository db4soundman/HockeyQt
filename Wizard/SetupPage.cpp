#include "SetupPage.h"
#include "MiamiAllAccessHockey.h"
#include "School.h"
#include <QGridLayout>
#include <QFileDialog>
#include <QColorDialog>
#include <QStandardPaths>
#include <QTextStream>
#include <QMessageBox>


SetupPage::SetupPage(QString* pSponsor, QString* pAnnouncer, QColor* pBg, QString* pStatCrew,
                     bool *pUsingTricaster, QString* tricasterIp, int *portNum) {
    chooseBg.setText("Background Color");
    browseStatCrew.setText("GameFile");
    ipHelp.setText("How do I determine this?");
    sponsor = (pSponsor);
    announcer = (pAnnouncer);
    statCrew = pStatCrew;
    bg = pBg;
    usingTricaster = pUsingTricaster;
    this->tricasterIp = tricasterIp;
    port = portNum;
    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget(&chooseBg, 4, 0);
    sponsorLine.setText(*sponsor);
    mainLayout->addWidget(new QLabel("Sponsor:"), 5, 0);
    mainLayout->addWidget(&sponsorLine, 5, 1);
    mainLayout->addWidget(new QLabel("Announcers"), 6, 0);
    mainLayout->addWidget(&announcerLine, 6, 1);
    tricasterBox = new QCheckBox("Using Tricaster");
    tricasterBox->setChecked(true);
    mainLayout->addWidget(tricasterBox, 8, 0);
    tricasterIpLine.setText(*tricasterIp);
    mainLayout->addWidget(&tricasterIpLine, 8, 1);
    mainLayout->addWidget(&ipHelp,8, 2);
    mainLayout->addWidget(new QLabel("Net Input"),8, 3);
    portSelector = new QComboBox();
    mainLayout->addWidget(portSelector,8, 4);

    portSelector->addItem("1");
    portSelector->addItem("2");

    setLayout(mainLayout);

    connect(&chooseBg, SIGNAL(clicked()), this, SLOT(bgDiag()));
    connect(&browseStatCrew, SIGNAL(clicked()), this, SLOT(statCrewBrowse()));
    connect(&ipHelp, SIGNAL(clicked()), this, SLOT(showHelp()));

    announcerLine.setText(*announcer);
    setTitle("Game Information");
}

bool SetupPage::validatePage()
{
    *sponsor = sponsorLine.text();
    *announcer = announcerLine.text();
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
