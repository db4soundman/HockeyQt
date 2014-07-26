#include "NchcGameGui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

NchcGameGui::NchcGameGui(bool firstGui) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* topLabels = new QHBoxLayout();
    QHBoxLayout* awayRow = new QHBoxLayout();
    QHBoxLayout* homeRow = new QHBoxLayout();
    topLabels->addWidget(new QLabel("Team"));
    topLabels->addWidget(new QLabel("Score"));
    topLabels->addWidget(new QLabel("Time and Pd"));
    awayRow->addWidget(&away);
    awayRow->addWidget(&awayScore);
    awayRow->addWidget(&timeAndPd);
    homeRow->addWidget(&home);
    homeRow->addWidget(&homeScore);
    homeRow->addWidget(&confGame);
    confGame.setText("NCHC Game");
    if (firstGui) {
        mainLayout->addLayout(topLabels);
    }
    mainLayout->addLayout(awayRow);
    mainLayout->addLayout(homeRow);
    setLayout(mainLayout);

    connect(&away, SIGNAL(textChanged(QString)), this, SIGNAL(awayNameUpdated(QString)));
    connect(&home, SIGNAL(textChanged(QString)), this, SIGNAL(homeNameUpdated(QString)));
}

void NchcGameGui::updateAwayName(QString name)
{
    away.setText(name);
}

void NchcGameGui::updateHomeName(QString name)
{
    home.setText(name);
}
