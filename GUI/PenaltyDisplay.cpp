#include "PenaltyDisplay.h"
#include <QFile>
#include <QTextStream>
#include "MiamiAllAccessHockey.h"


PenaltyDisplay::PenaltyDisplay(HockeyGame* game, bool homeTeam, bool standAlone) {
    playerSelector.addItems(homeTeam ? game->getHomeTeam()->getGuiNames() :
                                       game->getAwayTeam()->getGuiNames());

    QFile file(MiamiAllAccessHockey::getPenaltiesFilePath());
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream textStream(&file);

    while (!textStream.atEnd())
        penaltySelector.addItem(textStream.readLine().toUpper());

    show.setText("Show Penalty Text");

    connect(&show, SIGNAL(clicked()), this, SLOT(prepareSignal()));

    if (homeTeam) {
        connect(this, SIGNAL(callForPenaltyText(int,QString)),
                game, SLOT(prepareHomePenaltyText(int,QString)));
    }
    else {
        connect(this, SIGNAL(callForPenaltyText(int,QString)),
                game, SLOT(prepareAwayPenaltyText(int,QString)));
    }

    if (standAlone) {
        setLayout(createLayout());
    }

}

void PenaltyDisplay::prepareSignal()
{
    emit callForPenaltyText(playerSelector.currentIndex(), penaltySelector.currentText());
}


QHBoxLayout* PenaltyDisplay::createLayout()
{
    QHBoxLayout* myLayout = new QHBoxLayout();
    myLayout->addWidget(&playerSelector);
    myLayout->addWidget(&penaltySelector);
    myLayout->addWidget(&show);

    return myLayout;
}
