#include "PpClockDialog.h"
#include <QList>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include "ClockDialog.h"

PpClockDialog::PpClockDialog(HockeyGame* game) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QGridLayout* clocks = new QGridLayout();
    clocks->addWidget(new QLabel(game->getAwayName()), 0, 0);
    clocks->addWidget(new QLabel(game->getHomeName()), 0, 1);

    QList<Clock*> awayPenalties = game->getAwayPenalty();
    QList<Clock*> homePenalties = game->getHomePenalty();
    for (int i = 0; i < awayPenalties.size(); i++) {
        clocks->addWidget(new ClockDialog(awayPenalties[i]), i + 1, 0);
    }
    for (int i = 0; i < homePenalties.size(); i++) {
        clocks->addWidget(new ClockDialog(homePenalties[i]), i + 1, 1);
    }
    mainLayout->addLayout(clocks);
     QPushButton* ok = new QPushButton("Close");
     mainLayout->addWidget(ok);
     setLayout(mainLayout);
     setWindowTitle("Adjust Penalty Clocks");

     connect(ok, SIGNAL(clicked()), this, SLOT(reject()));
     connect(this, SIGNAL(rejected()), game, SLOT(determinePpClockForScoreboard()));

}



