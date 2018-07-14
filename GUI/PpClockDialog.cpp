#include "PpClockDialog.h"
#include <QList>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include "ClockDialog.h"
#include "MiamiAllAccessHockey.h"

PpClockDialog::PpClockDialog(HockeyGame* game) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QGridLayout* clocks = new QGridLayout();
    clocks->addWidget(new QLabel(MiamiAllAccessHockey::awaySchool.getShortName()), 0, 0);
    clocks->addWidget(new QLabel(MiamiAllAccessHockey::homeSchool.getShortName()), 0, 1);

    QList<Clock*> awayPenalties = game->getAwayPenalty();
    QList<Clock*> homePenalties = game->getHomePenalty();
    for (int i = 0, spot = 1; i < awayPenalties.size(); i++) {
        if (awayPenalties.at(i)->getTimeLeft() != 0) {
            clocks->addWidget(new ClockDialog(awayPenalties[i]), spot, 0);
            spot++;
        }
    }
    for (int i = 0, spot = 1; i < homePenalties.size(); i++) {
        if (homePenalties.at(i)->getTimeLeft() != 0) {
            clocks->addWidget(new ClockDialog(homePenalties[i]), spot, 1);
            spot++;
        }
    }
    mainLayout->addLayout(clocks);
    QPushButton* ok = new QPushButton("Close");
    mainLayout->addWidget(ok);
    setLayout(mainLayout);
    setWindowTitle("Adjust Penalty Clocks");

    connect(ok, SIGNAL(clicked()), this, SLOT(reject()));
    connect(this, SIGNAL(rejected()), game, SLOT(determinePpClockForScoreboard()));

}



