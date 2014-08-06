#include "TeamEditor.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>

TeamEditor::TeamEditor(HockeyTeam* pTeam) {
    team = pTeam;
    setWindowTitle("Team Editor");
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QFormLayout* spinBoxes = new QFormLayout();
    spinBoxes->addRow("Powerplay Goals Today", &ppg);
    spinBoxes->addRow("Powerplay Opp. Today", &ppopp);
    spinBoxes->addRow("Penalty Kills Today", &pk);
    spinBoxes->addRow("Penalty Kill Opp. Today", &pkopp);
    mainLayout->addLayout(spinBoxes);
    QPushButton* ok = new QPushButton("Ok");
    connect(ok, SIGNAL(clicked()), this, SLOT(changeStats()));
    connect(ok, SIGNAL(clicked()), this, SLOT(hide()));
    mainLayout->addWidget(ok);
    setLayout(mainLayout);
    ppgS = team->getPpg();
    ppoppS = team->getPpopp();
    pkS = team->getPk();
    pkoppS = team->getPkopp();

}

void TeamEditor::updateSpinBoxes()
{
    ppg.setValue(team->getPpgToday());
    ppopp.setValue(team->getPpoppToday());
    pk.setValue(team->getPkToday());
    pkopp.setValue(team->getPkoppToday());
}

void TeamEditor::changeStats()
{
    team->setPpg(ppgS + ppg.value());
    team->setPpopp(ppoppS + ppopp.value());
    team->setPk(pkS + pk.value());
    team->setPkopp(pkoppS + pkopp.value());

    team->setPpgToday(ppg.value());
    team->setPpoppToday(ppopp.value());
    team->setPkToday(pk.value());
    team->setPkoppToday(pkopp.value());
}
