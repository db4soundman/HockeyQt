#include "Scoreboard.h"

Scoreboard::Scoreboard(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/Scoreboard.png"));
    ppBar = new QPixmap(":/images/ppBar.png");
    topBar = new QPixmap(":/images/statbar.png");
    //ppBar->setScale(1.67);
    //ppBar->setY(54);
}

void
Scoreboard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
    painter->drawPixmap(0,-49, *topBar);
    painter->drawPixmap(0,0,this->pixmap());
    //ppBar->paint(painter, option, widget);
    // Away ppbar
    painter->drawPixmap(112,52, *ppBar);
    //Home
    painter->drawPixmap(466,52, *ppBar);
    //Neutral
    painter->drawPixmap(830,54,257,38, *ppBar );

}
