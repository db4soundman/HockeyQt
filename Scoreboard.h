#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QObject>
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QList>
#include "Clock.h"
#include <QString>

class Scoreboard : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
     Scoreboard(QColor awayCol, QColor homeCol, QString awayTeam, QString homeTeam,
                 QString sponsorText, Clock* clock, QGraphicsItem* parent = 0);
     void paint(QPainter * painter,
                const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

signals:

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

private:
     QPixmap* ppBar;
     QPixmap* topBar;
     QPixmap* networkLogo;
     QColor homeColor, awayColor;
     QGraphicsTextItem* homeName;
     QGraphicsTextItem* awayName;
     QGraphicsTextItem* homeScore;
     QGraphicsTextItem* awayScore;
     QGraphicsTextItem* topBarText;
     QString ppDescription, period, centeredTimeText, sponsorText;
     QLinearGradient homeGradient, awayGradient, penaltyGradient;
     bool awayPP, homePP, neutralPP, penalty, sponsor,
     scoreText, showPP, show, showPdAndClock, showClock;

     void prepareColor();
     Clock* clock;
     Clock* ppClock;

};

#endif
