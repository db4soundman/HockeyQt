#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QObject>
#include <QPainter>

class Scoreboard : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
     Scoreboard(QGraphicsItem* parent = 0);
     void paint(QPainter * painter,
                const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

signals:

public slots:

private:
     //QPixmap scoreboard;
     //QGraphicsPixmapItem* ppBar;
     QPixmap* ppBar;
     QPixmap* topBar;
     QPixmap* networkLogo;
     QGraphicsTextItem* homeName;
     QGraphicsTextItem* awayName;
     QGraphicsTextItem* homeScore;
     QGraphicsTextItem* awayScore;
     QGraphicsTextItem* topBarText;
     QLinearGradient homeGradient, awayGradient, penaltyGradient;
     bool awayPP, homePP, neutralPP, penalty, sponsor, scoreText;


};

#endif
