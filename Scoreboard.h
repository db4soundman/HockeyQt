#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QObject>
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QList>
#include "Clock.h"
#include <QString>

class Scoreboard : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
     Scoreboard(QColor awayCol, QColor homeCol, QString awayTeam, QString homeTeam,
                 QString sponsorText, Clock* clock, QString pAwayRank, QString pHomeRank, QPixmap pawayLogo);
     void paint(QPainter * painter,
                const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

     bool getUseTransparency() const;
     void setUseTransparency(bool value);
     int getRealWidth();

     bool getShowClock() const;

signals:
     void sceneUpdated(int x, int y, int w, int h);
     void transparentField(int x, int y, int w, int h);
     void removeTransparentField(int x, int y, int w, int h);

public slots:
     void togglePenalty();
     void showPd();
     void final();
     void preparePowerplayClock(int pos, Clock* clock = NULL, QString description = "");
     void updateHomeScore(int score);
     void updateAwayScore(int score);
     void updatePeriod(int pd);
     void changeTopBarText(QString text);
     void toggleShowBoard();
     void togglePpClocks();
     void hideBoard();
     void updateClock();
     void intermission();
     void displayClock();
     void displaySponsor();
     void changeUseClock(bool uc);

private:
     QPixmap* ppBar;
     QPixmap* topBar;
     QPixmap* homeLogo, *awayLogo;
     QColor homeColor, awayColor;
     QGraphicsTextItem* homeName;
     QGraphicsTextItem* awayName;
     QGraphicsTextItem* homeScore;
     QGraphicsTextItem* awayScore;
     QGraphicsTextItem* topBarText;
     QGraphicsTextItem* awayRank;
     QGraphicsTextItem* homeRank;
     QString ppDescription, period, centeredTimeText, sponsorText;
     QLinearGradient homeGradient, awayGradient, penaltyGradient, mainGradient, clockGradient, ppGradient, scoreGradient, bgGradient;
     bool awayPP, homePP, neutralPP, penalty, sponsor, useClock,
     scoreText, showPP, show, showPdAndClockFields, showClock, useTransparency;

     void prepareColor();
     void prepareAwayName();
     Clock* clock;
     Clock* ppClock;
     QFont defaultSponsorText;
     int homeRankOffset, awayRankOffset, homeLogoOffset, awayLogoOffset, pd;

};

#endif
