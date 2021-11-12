#include "Ticker.h"
#include <QGraphicsScene>

#define WIDTH 1920

Ticker::Ticker()
{
    timer.setInterval(1000 * 10); // 10 seconds
    connect(&timer, SIGNAL(timeout()), this, SLOT(advanceTicker()));
    //game = pgame;
    show = false;
    prepareColor();
    setRect(0,0,WIDTH,74);
}

void Ticker::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (show) {
        painter->fillRect(0,0,WIDTH, 74, mainGradient);
        painter->fillRect(100, 2, WIDTH - 200, 44, QColor(1,1,1));
        painter->setFont(resizeText());
        painter->setPen(QColor(255,255,255));
        painter->drawText(100, 2, 400, 44, Qt::AlignCenter, games[index].getAway());
        painter->drawText(500, 2, 100, 44, Qt::AlignCenter, games[index].getAwayScore());
        painter->drawText(600, 2, 400, 44, Qt::AlignCenter, games[index].getHome());
        painter->drawText(1000, 2, 100, 44, Qt::AlignCenter, games[index].getHomeScore());
        painter->drawText(1100, 2, 300, 44, Qt::AlignCenter, games[index].getTimeAndPd());
    }
}

void Ticker::setFridayGames(const QList<NchcScoreEntry> &value)
{
    games.clear();
    games = value;
}

void Ticker::setSaturdayGames(const QList<NchcScoreEntry> &value)
{
    games.append(value);
}

void Ticker::advanceTicker()
{
    index = (index + 1) % games.size();
    scene()->update(0, this->y(), WIDTH, 74);
}

void Ticker::showTicker()
{
    index = 0;
    show = true;
    timer.start();
    scene()->update(0, this->y(), WIDTH, 74);
}

void Ticker::hideTicker()
{
    if (show) {
        show = false;
        timer.stop();
        scene()->update(0, this->y(), WIDTH, 74);
    }
}

void Ticker::prepareColor()
{
    mainGradient.setStart(0,0);
    mainGradient.setFinalStop(0, 74);
    mainGradient.setColorAt(0, QColor(41, 70, 91));
    mainGradient.setColorAt(1, QColor(23, 41, 53));
}

QFont Ticker::resizeText()
{
    int subtraction = 0;
    int fontPointSize = 24;
    QFontMetrics fontSize(QFont("Arial", 24, QFont::Bold));
//    while (fontSize.width(players.at(index)->toString()) > WIDTH - 205) {
//        QFont tempFont("Arial", fontPointSize - subtraction, QFont::Bold);
//        subtraction++;
//        QFontMetrics temp(tempFont);
//        fontSize = temp;
//    }
    return QFont("Arial", 24 - subtraction, QFont::Bold);
}

