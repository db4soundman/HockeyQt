#include "StandingsGraphic.h"
#include <QGraphicsScene>

StandingsGraphic::StandingsGraphic(QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/Standings.png"));
    show = false;
}

void StandingsGraphic::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                             QWidget* widget) {
    if (show) {
        int fontSize = 32;
#ifdef Q_OS_OSX
        fontSize = 40;
#endif
        painter->setFont(QFont("Arial", fontSize, QFont::Bold));
        painter->setBrush(QColor(255,255,255));
        painter->setPen(QColor(255,255,255));
        painter->drawPixmap(0, 0, this->pixmap());
        painter->drawText(0, 0, 1920, 80, Qt::AlignCenter, "NCHC STANDINGS");
        painter->drawText(1100, 110, 140, 100, Qt::AlignRight | Qt::AlignVCenter, "W");
        painter->drawText(1240, 110, 140, 100, Qt::AlignRight | Qt::AlignVCenter, "L");
        painter->drawText(1380, 110, 140, 100, Qt::AlignRight | Qt::AlignVCenter, "T");
        painter->drawText(1520, 110, 140, 100, Qt::AlignRight | Qt::AlignVCenter, "PTS");

        for (int i = 0; i < nchcStandings.size(); i++) {
            painter->fillRect(0, 200 + (100*i), 1920, 50, QColor(165, 0, 22, 200));
            painter->drawText(0, 200 + (100*i), 700, 50, Qt::AlignRight | Qt::AlignVCenter, nchcStandings.at(i).getTeamName());
            painter->drawText(1100, 200 + (100*i), 140, 50, Qt::AlignRight | Qt::AlignVCenter, QString::number(nchcStandings.at(i).getWins()));
            painter->drawText(1240, 200 + (100*i), 140, 50, Qt::AlignRight | Qt::AlignVCenter, QString::number(nchcStandings.at(i).getLosses()));
            painter->drawText(1380, 200 + (100*i), 140, 50, Qt::AlignRight | Qt::AlignVCenter, QString::number(nchcStandings.at(i).getTies()));
            painter->drawText(1520, 200 + (100*i), 140, 50, Qt::AlignRight | Qt::AlignVCenter, QString::number(nchcStandings.at(i).getPoints()));
        }
    }
}

void StandingsGraphic::updateStandings(QList<StandingsEntry> list)
{
    nchcStandings = list;
}

void StandingsGraphic::toggleShow()
{
    show = true;
    scene()->update();
}

void StandingsGraphic::hide()
{
    if (show) {
        show = false;
        scene()->update();
    }
}
