#include "NchcGameGui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>

NchcGameGui::NchcGameGui() {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* topLabels = new QHBoxLayout();
    QFormLayout* teamRow = new QFormLayout();
    QFormLayout* scoreRow = new QFormLayout();
    teamRow->addRow("Away Team:", &away);
    scoreRow->addRow("Score:" , &awayScore);
    teamRow->addRow("Home Team:", &home);
    scoreRow->addRow("Score:",&homeScore);
    teamRow->addRow("Time pd ", &timeAndPd);
    scoreRow->addRow("", &confGame);
    confGame.setText("NCHC Game");
    topLabels->addLayout(teamRow);
    topLabels->addLayout(scoreRow);
    mainLayout->addLayout(topLabels);
//    mainLayout->addLayout(scoreRow);
    setLayout(mainLayout);

    connect(&away, SIGNAL(textChanged(QString)), this, SIGNAL(awayNameUpdated(QString)));
    connect(&home, SIGNAL(textChanged(QString)), this, SIGNAL(homeNameUpdated(QString)));
    connect(&confGame, SIGNAL(toggled(bool)), this, SIGNAL(confGameUpdated(bool)));
}

void NchcGameGui::setConf(bool pConf)
{
    confGame.setChecked(pConf);
}

void NchcGameGui::setTimeAndPd(QString tap)
{
    timeAndPd.setText(tap);
}

void NchcGameGui::setAwayScore(QString scr)
{
    awayScore.setText(scr);
}

void NchcGameGui::setHomeScore(QString scr)
{
    homeScore.setText(scr);
}

void NchcGameGui::updateAwayName(QString name)
{
    away.setText(name);
}

void NchcGameGui::updateHomeName(QString name)
{
    home.setText(name);
}

void NchcGameGui::updateConfGame(bool isConfGame)
{
    confGame.setChecked(isConfGame);
}
