#include "GameInfo.h"
#include <QGridLayout>

GameInfo::GameInfo(HockeyGame* game) {
    QGridLayout* main = new QGridLayout();
    awayTeamName.setText(game->getAwayTri());
    main->addWidget(&awayTeamName, 0, 0);
    homeTeamName.setText(game->getHomeTri());
    main->addWidget(&homeTeamName, 1, 0);
    awayTeamScore.setText("0");
    main->addWidget(&awayTeamScore, 0, 1);
    homeTeamScore.setText("0");
    main->addWidget(&homeTeamScore, 1, 1);
    pd.setText("Pd: 0");
    main->addWidget(&pd, 2, 0);
    clock = game->getGameClock();
    time.setText(clock->toString());
    main->addWidget(&time, 2, 1);

    connect(clock, SIGNAL(clockUpdated()), this, SLOT(updateTime()));
    connect(game, SIGNAL(awayScoreChanged(int)), this, SLOT(updateAwayScore(int)));
    connect(game, SIGNAL(homeScoreChanged(int)), this, SLOT(updateHomeScore(int)));
    connect(game, SIGNAL(periodChanged(int)), this, SLOT(updatePeriod(int)));
    connect(game, SIGNAL(clockInUse(bool)), this, SLOT(changeUseClock(bool)));

    setLayout(main);
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
