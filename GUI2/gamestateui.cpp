#include "gamestateui.h"
#include <QFormLayout>
#include <QVBoxLayout>
GameStateUI::GameStateUI(HockeyGame* game):goalieUi(game)
{
    this->game = game;
    QVBoxLayout* masterLayout = new QVBoxLayout();
    QFormLayout* myLayout = new QFormLayout();
    myLayout->addRow("Time", &time);
    myLayout->addRow("Away Score", &awayScore);
    myLayout->addRow("Home Score", &homeScore);
    myLayout->addRow("Away TOL", &awayTol);
    myLayout->addRow("Home TOL", &homeTol);
    myLayout->addRow("Away Ply 1", &awayP1);
    myLayout->addRow("Away Pen 1", &awayClock1);
    myLayout->addRow("Away Ply 2", &awayP2);
    myLayout->addRow("Away Pen 2", &awayClock2);
    myLayout->addRow("Home Ply 1", &homeP1);
    myLayout->addRow("Home Pen 1", &homeClock1);
    myLayout->addRow("Home Ply 2", &homeP2);
    myLayout->addRow("Home Pen 2", &homeClock2);

    masterLayout->addLayout(myLayout);
    masterLayout->addWidget(&goalieUi);

    setLayout(masterLayout);

}

GameStateUI::~GameStateUI()
{

}

void GameStateUI::updateData(QByteArray data)
{
    try {
        QString clock = data.mid(1, 7);
        bool stopped = data.mid(8,1) == "s";
        QString homeScoreS = data.mid(9,2).trimmed();
        QString awayScoreS = data.mid(11,2).trimmed();
        QString homeTol = data.mid(13,1);
        QString awayTol = data.mid(14,1);
        int hSog = data.mid(15,2).toInt();
        int aSog = data.mid(17,2).toInt();
        int cgPeriod = data.mid(19,2).toInt();


        QString homePlayer1 = data.mid(21,2);
        QString homePen1 = data.mid(23,5).trimmed();
        QString homePlayer2 = data.mid(28,2);
        QString homePen2 = data.mid(30,5).trimmed();
        QString awayPlayer1 = data.mid(35,2);
        QString awayPen1 = data.mid(37,5).trimmed();
        QString awayPlayer2 = data.mid(42,2);
        QString awayPen2 = data.mid(44,5).trimmed();

        time.setText(clock);
        awayScore.setText(awayScoreS);
        homeScore.setText(homeScoreS);
        this->homeTol.setText(homeTol);
        this->awayTol.setText(awayTol);

        awayP1.setText(awayPlayer1);
        awayClock1.setText(awayPen1);

        awayP2.setText(awayPlayer2);
        awayClock2.setText(awayPen2);

        homeP1.setText(homePlayer1);
        homeClock1.setText(homePen1);

        homeP2.setText(homePlayer2);
        homeClock2.setText(homePen2);


        //toggleCgPenaltyClocks(!stopped);
    } catch (...) {
    }
}

