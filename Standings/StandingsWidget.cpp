#include "StandingsWidget.h"
#include <QStringList>
#include <QLabel>
#include <QPushButton>

StandingsWidget::StandingsWidget(StandingsGraphic* graphic) {
    mainLayout = new QGridLayout();
    QStringList teams;
    teams.append("DENVER");
    teams.append("COLORADO COLLEGE");
    teams.append("MIAMI");
    teams.append("MINNESOTA-DULUTH");
    teams.append("NEBRASKA-OMAHA");
    teams.append("NORTH DAKOTA");
    teams.append("ST. CLOUD STATE");
    teams.append("WESTERN MICHIGAN");
    mainLayout->addWidget(new QLabel("Team"), 0, 0);
    mainLayout->addWidget(new QLabel("Wins"), 0, 1);
    mainLayout->addWidget(new QLabel("Losses"), 0 , 2);
    mainLayout->addWidget(new QLabel("Ties"), 0, 3);
    mainLayout->addWidget(new QLabel("SO Wins"), 0, 4);
    for (int i = 0; i < teams.size(); i++) {
        QComboBox* box = new QComboBox();
        box->addItems(teams);
        teamSelectors.append(box);
        QSpinBox* spin = new QSpinBox();
        wins.append(spin);
        spin = new QSpinBox();
        losses.append(spin);
        spin = new QSpinBox();
        ties.append(spin);
        spin = new QSpinBox();
        shootoutWins.append(spin);
        mainLayout->addWidget(teamSelectors.at(i), i+1, 0);
        mainLayout->addWidget(wins.at(i), i+1, 1);
        mainLayout->addWidget(losses.at(i), i+1, 2);
        mainLayout->addWidget(ties.at(i), i+1, 3);
        mainLayout->addWidget(shootoutWins.at(i), i+1, 4);
    }
    QPushButton* okButton = new QPushButton("Ok");
    connect(okButton, SIGNAL(clicked()), this, SLOT(compileStandings()));
    connect(this, SIGNAL(shareStandings(QList<StandingsEntry>)),
            graphic, SLOT(updateStandings(QList<StandingsEntry>)));
    mainLayout->addWidget(okButton, 9, 5);
    setLayout(mainLayout);
}

void StandingsWidget::compileStandings()
{
    QList<StandingsEntry> standings;
    for (int i = 0; i < teamSelectors.size(); i++) {
        StandingsEntry temp(teamSelectors.at(i)->currentText(), wins.at(i)->value(),
                            losses.at(i)->value(), ties.at(i)->value(), shootoutWins.at(i)->value());
        standings.append(temp);
    }
    emit shareStandings(standings);
    this->hide();
}
