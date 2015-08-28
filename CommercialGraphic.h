#ifndef COMMERCIALGRAPHIC_H
#define COMMERCIALGRAPHIC_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFont>
#include "HockeyGame.h"
#include <QLinearGradient>
#include <QPainter>
#include <QGraphicsTextItem>

class CommercialGraphic : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    CommercialGraphic(HockeyGame* game, QString pawayLogo, QGraphicsItem *parent = 0);

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

signals:

public slots:
    void prepareAndShow();
    void updateClock();
    void showClock();
    void intermissionTime();
    void finalTime();
    void hide();

private:
    QPixmap blackBar;
    QLinearGradient homeTeamGradient, awayTeamGradient, clockGradient, bgGradient;
    HockeyGame* hockeyGame;
    bool show, inGame;
    QGraphicsTextItem* away, *home;
    QString homeScore, awayScore, networkText, period, clock;
    QFont descriptiveFont;
    int clockStatus;
    void checkAwayFont();
    void prepareGradients(QColor awayColor, QColor homeColor);
    QPixmap homeLogo, *awayLogo;
    // yep, a test
};

#endif // COMMERCIALGRAPHIC_H
