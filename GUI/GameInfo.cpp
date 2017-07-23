#include "GameInfo.h"
#include <QGridLayout>

GameInfo::GameInfo(HockeyGame* game) {
    QGridLayout* myLayout = new QGridLayout();
    awayTeamName.setText(game->getAwayTri());
    myLayout->addWidget(&awayTeamName, 0, 0);
    homeTeamName.setText(game->getHomeTri());
    myLayout->addWidget(&homeTeamName, 1, 0);
    awayTeamScore.setText("0");
    myLayout->addWidget(&awayTeamScore, 0, 1);
    homeTeamScore.setText("0");
    myLayout->addWidget(&homeTeamScore, 1, 1);
    pd.setText("Pd: 0");
    myLayout->addWidget(&pd, 2, 0);
    clock = game->getGameClock();
    time.setText(clock->toString());
    myLayout->addWidget(&time, 2, 1);
    useClock = true;
    connect(clock, SIGNAL(clockUpdated()), this, SLOT(updateTime()));
    connect(game, SIGNAL(awayScoreChanged(int)), this, SLOT(updateAwayScore(int)));
    connect(game, SIGNAL(homeScoreChanged(int)), this, SLOT(updateHomeScore(int)));
    connect(game, SIGNAL(periodChanged(int)), this, SLOT(updatePeriod(int)));
    connect(game, SIGNAL(clockInUse(bool)), this, SLOT(changeUseClock(bool)));

    setLayout(myLayout);
}

void
GameInfo::updateTime() {
    if (Q_LIKELY(useClock))
        time.setText(clock->toString());
}

void GameInfo::updateHomeScore(int score) {
    homeTeamScore.setText(QString::number(score));
}

void GameInfo::updateAwayScore(int score) {
    awayTeamScore.setText(QString::number(score));
}

void GameInfo::updatePeriod(int newPd) {
    pd.setText("Pd: " + QString::number(newPd));
}

void GameInfo::changeUseClock(bool uc)
{
    useClock = uc;
    if (useClock)
        updateTime();
    else time.setText( "PD");
}
