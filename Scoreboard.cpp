#include "Scoreboard.h"

Scoreboard::Scoreboard(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/Scoreboard.png"));
    ppBar = new QPixmap(":/images/ppBar.png");
    topBar = new QPixmap(":/images/statbar.png");
    networkLogo = new QPixmap(":/images/M.png");
    awayName = new QGraphicsTextItem("WINDSOR");
    homeName = new QGraphicsTextItem("MIAMI");
    awayName->setFont(QFont("Arial", 40, QFont::Bold));
    homeName->setFont(QFont("Arial", 40, QFont::Bold));
    awayScore = new QGraphicsTextItem("100");
    awayScore->setFont(QFont("Arial", 40, QFont::Bold));
    homeScore = new QGraphicsTextItem("100");
    homeScore->setFont(QFont("Arial", 40, QFont::Bold));

    topBarText = new QGraphicsTextItem("McCullough Hyde Memorial Hospital - IMG Sports Network");
    topBarText->setFont(QFont("Arial", 14*2, QFont::Bold));

    // need a lerp color method
    homeGradient.setFinalStop(0,43);
    awayGradient.setFinalStop(0,43);
    homeGradient.setColorAt(0, QColor(220,0,0));
    homeGradient.setColorAt(1, QColor(140,0,0));
    awayGradient.setColorAt(0, QColor(0,0,224));
    awayGradient.setColorAt(1, QColor(0,0,0));

    // penalty gradient
    penaltyGradient.setStart(0, 54);
    penaltyGradient.setFinalStop(0, 92);
    penaltyGradient.setColorAt(0, QColor(255, 255, 0));
    penaltyGradient.setColorAt(1, QColor(188, 188, 0));

}

void
Scoreboard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
    painter->drawPixmap(0,-49, *topBar);
    painter->drawPixmap(0,0,this->pixmap());
    painter->drawPixmap(34, 4, 73, 46, *networkLogo);
    //Clock - Game time...draw clock first since default color is black
    painter->setFont(QFont("Arial", 40, QFont::Bold));
    painter->drawText(838, 3, 247, 50, Qt::AlignVCenter, "1st");
    painter->drawText(833, 3, 242, 50, Qt::AlignRight | Qt::AlignVCenter, "20:00");
    //StatBarText
    painter->setPen(QColor(255, 255, 255));
    painter->setFont(topBarText->font());
    painter->drawText(0, -49, 1102, 49, Qt::AlignCenter, topBarText->toPlainText());

    // Away ppbar
    painter->drawPixmap(112,52, *ppBar);
    painter->setPen(QColor(255, 255, 255));
    painter->setFont(QFont("Arial", 32, QFont::Bold));
    painter->drawText(120, 52, 345, 38, Qt::AlignLeft | Qt::AlignVCenter, "POWERPLAY");
    painter->drawText(120, 52, 331, 38, Qt::AlignRight | Qt::AlignVCenter, "2:00");
    //Home ppbar
    painter->drawPixmap(466,52, *ppBar);
    painter->setPen(QColor(255, 255, 255));
    painter->setFont(QFont("Arial", 32, QFont::Bold));
    painter->drawText(474, 52, 345, 38, Qt::AlignLeft | Qt::AlignVCenter, "POWERPLAY");
    painter->drawText(474, 52, 331, 38, Qt::AlignRight | Qt::AlignVCenter, "2:00");
    //Neutral
    painter->drawPixmap(833,54,247,38, *ppBar );
    painter->setPen(QColor(255, 255, 255));
    painter->setFont(QFont("Arial", 32, QFont::Bold));
    painter->drawText(841, 54, 247, 38, Qt::AlignLeft | Qt::AlignVCenter, "4-ON-4");
    painter->drawText(833, 54, 239, 38, Qt::AlignRight | Qt::AlignVCenter, "2:00");

    // Away text
    painter->fillRect(115, 6, 260, 42, awayGradient );
    painter->setFont(awayName->font());
    painter->setPen(QColor(255, 255, 255));
    painter->drawText(118, 6, 260, 42, Qt::AlignVCenter, awayName->toPlainText());
    // Away Score
    painter->setFont(awayScore->font());
    painter->drawText(374, 6, 78, 44, Qt::AlignCenter, awayScore->toPlainText());
    //painter->drawText(416, 43, homeScore->toPlainText());

    // Home Text
    painter->fillRect(470, 6, 260, 42, homeGradient );
    painter->setFont(homeName->font());
    painter->drawText(475, 6, 260, 42, Qt::AlignVCenter, homeName->toPlainText());
    // Home Score
    painter->setFont(homeScore->font());
    painter->drawText(728, 6, 78, 44, Qt::AlignCenter, homeScore->toPlainText());

/*
    // Penalty Indicator
    painter->fillRect(833, 52, 247, 38, penaltyGradient);
    painter->setPen(QColor(0,0,0));
    painter->setFont(QFont("Arial", 32, QFont::Bold));
    painter->drawText(833,54,247,38, Qt::AlignCenter, "PENALTY");
    */

}
