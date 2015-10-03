#include "PenaltyDisplay.h"
#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>
#include "MiamiAllAccessHockey.h"

PenaltyDisplay::PenaltyDisplay(HockeyGame* game, bool homeTeam) {
    playerSelector.addItems(homeTeam ? game->getHomeTeam()->getGuiNames() :
                                       game->getAwayTeam()->getGuiNames());

    QFile file(MiamiAllAccessHockey::getPenaltiesFilePath());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textStream(&file);

    while (!textStream.atEnd())
        penaltySelector.addItem(textStream.readLine().toUpper());

    show.setText("Show Penalty Text");

    QHBoxLayout* main = new QHBoxLayout();
    main->addWidget(&playerSelector);
    main->addWidget(&penaltySelector);
    main->addWidget(&show);

    connect(&show, SIGNAL(clicked()), this, SLOT(prepareSignal()));

    if (homeTeam) {
        connect(this, SIGNAL(callForPenaltyText(int,QString)),
                game, SLOT(prepareHomePenaltyText(int,QString)));
    }
    else {
        connect(this, SIGNAL(callForPenaltyText(int,QString)),
                game, SLOT(prepareAwayPenaltyText(int,QString)));
    }

    setLayout(main);

}

void PenaltyDisplay::prepareSignal()
{
    emit callForPenaltyText(playerSelector.currentIndex(), penaltySelector.currentText());
}
