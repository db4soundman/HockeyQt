#include "NchcScoreboardGraphic.h"
#include <QGraphicsScene>

#define BORDER_WIDTH 650
#define IMAGE_WIDTH 117
#define BORDER_HEIGHT 120

NchcScoreboardGraphic::NchcScoreboardGraphic() {
    setPixmap(QPixmap(":/images/Standings.png"));
    show = false;
}

void
NchcScoreboardGraphic::paint(QPainter* painter,
                             const QStyleOptionGraphicsItem* option,
                             QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (show) {
        int fontSize = 34;
#ifdef Q_OS_OSX
        fontSize = 40;
#endif
        painter->setFont(QFont("Arial", fontSize, QFont::Bold));
        painter->setBrush(QColor(255,255,255));
        painter->setPen(QColor(255,255,255));
        painter->drawPixmap(0, 0, this->pixmap());
        //painter->drawText(0, 0, 1920, 80, Qt::AlignCenter, "NCHC SCOREBOARD");
        painter->drawText(0, 0, 1920/2, 80, Qt::AlignCenter, "FRIDAY GAMES");
        painter->drawText(1920/2, 0, 1920/2, 80, Qt::AlignCenter, "SATURDAY GAMES");
        int spacing = (980 - (120*fridayGames.size())) / fridayGames.size();
        int x = 200;
        for (int i = 0; i < fridayGames.size(); i++) {
            // Outer border
            painter->fillRect(x, 80 + (BORDER_HEIGHT + spacing) * i, BORDER_WIDTH, BORDER_HEIGHT, fridayGames.at(i).getConfGame() ?
                                  QColor(165, 0, 22, 200) : QColor(0, 0, 0, 200));
            // Inner border
            painter->fillRect(x, 80 + (BORDER_HEIGHT + spacing) * i, BORDER_WIDTH - 150, BORDER_HEIGHT, QColor(0, 0, 0));
            painter->setBrush(QColor(255,255,255));
            painter->setPen(QColor(255,255,255));
            // School
            painter->drawText(x, 80 + (BORDER_HEIGHT + spacing) * i, 500, BORDER_HEIGHT / 2, Qt::AlignLeft, fridayGames.at(i).getAway());
            painter->drawText(x,80 + (BORDER_HEIGHT + spacing) * i + BORDER_HEIGHT / 2, 500, BORDER_HEIGHT / 2, Qt::AlignLeft, fridayGames.at(i).getHome());
            QString timePd = fridayGames.at(i).getTimeAndPd();
            timePd = timePd.replace(" ", "\n");
            painter->drawText(x + BORDER_WIDTH - 150, 80 + (BORDER_HEIGHT + spacing) * i, 150, BORDER_HEIGHT, Qt::AlignCenter, timePd);

            // Score
            painter->setBrush(QColor(253,180,26));
            painter->setPen(QColor(253,180,26));
            painter->drawText(x + 500 - 60, 80 + (BORDER_HEIGHT + spacing) * i, 53, BORDER_HEIGHT / 2, Qt::AlignVCenter | Qt::AlignRight, fridayGames.at(i).getAwayScore());
            painter->drawText(x + 500 - 60, BORDER_HEIGHT / 2 + 80 + (BORDER_HEIGHT + spacing) * i, 53, BORDER_HEIGHT / 2, Qt::AlignVCenter | Qt::AlignRight, fridayGames.at(i).getHomeScore());
            painter->fillRect(x, 80 + (BORDER_HEIGHT + spacing) * i + BORDER_HEIGHT / 2 - 5, BORDER_WIDTH - 150, 10, fridayGames.at(i).getConfGame() ?
                                  QColor(165, 0, 22) : QColor(255, 255, 255));
            if (fridayGames.at(i).getConfGame()) {
                painter->fillRect(x - IMAGE_WIDTH, 80 + (BORDER_HEIGHT + spacing) * i, IMAGE_WIDTH, BORDER_HEIGHT, fridayGames.at(i).getConfGame() ?
                                      QColor(165, 0, 22, 200) : QColor(0, 0, 0, 200));
                painter->drawPixmap(x - IMAGE_WIDTH, 80 + (BORDER_HEIGHT + spacing) * i, IMAGE_WIDTH, BORDER_HEIGHT, QPixmap(":/images/NCHClrg.png"));
            }
        }
        x = 1120 + IMAGE_WIDTH;
        for (int i = 0; i < saturdayGames.size(); i++) {
            // Outer border
            painter->fillRect(x ,80 + (BORDER_HEIGHT + spacing) * i, BORDER_WIDTH, BORDER_HEIGHT, saturdayGames.at(i).getConfGame() ?
                                  QColor(165, 0, 22, 200) : QColor(0, 0, 0, 200));
            // Inner border
            painter->fillRect(x, 80 + (BORDER_HEIGHT + spacing) * i, BORDER_WIDTH - 100, BORDER_HEIGHT, QColor(0, 0, 0));
            painter->setBrush(QColor(255,255,255));
            painter->setPen(QColor(255,255,255));
            // School
            painter->drawText(x, 80 + (BORDER_HEIGHT + spacing) * i, 500, BORDER_HEIGHT / 2, Qt::AlignLeft, saturdayGames.at(i).getAway());
            painter->drawText(x, BORDER_HEIGHT / 2 + 80 + (BORDER_HEIGHT + spacing) * i, 500, BORDER_HEIGHT / 2, Qt::AlignLeft, saturdayGames.at(i).getHome());
            QString timePd = saturdayGames.at(i).getTimeAndPd();
            timePd = timePd.replace(" ", "\n");
            painter->drawText(x + BORDER_WIDTH - 150, 80 + (BORDER_HEIGHT + spacing) * i, 150, BORDER_HEIGHT, Qt::AlignCenter, timePd);

            // Score
            painter->setBrush(QColor(253,180,26));
            painter->setPen(QColor(253,180,26));
            painter->drawText(x + 500-60, 80 + (BORDER_HEIGHT + spacing) * i, 53, BORDER_HEIGHT / 2, Qt::AlignVCenter | Qt::AlignRight, saturdayGames.at(i).getAwayScore());
            painter->drawText(x + 500-60, BORDER_HEIGHT / 2 + 80 + (BORDER_HEIGHT + spacing) * i, 53, BORDER_HEIGHT / 2, Qt::AlignVCenter | Qt::AlignRight, saturdayGames.at(i).getHomeScore());
            painter->fillRect(x, BORDER_HEIGHT / 2 - 5 + 80 + (BORDER_HEIGHT + spacing) * i, BORDER_WIDTH - 150, 10, saturdayGames.at(i).getConfGame() ?
                                  QColor(165, 0, 22) : QColor(255, 255, 255));
            if (saturdayGames.at(i).getConfGame()) {
                painter->fillRect(x - IMAGE_WIDTH, 80 + (BORDER_HEIGHT + spacing) * i, IMAGE_WIDTH, BORDER_HEIGHT, fridayGames.at(i).getConfGame() ?
                                      QColor(165, 0, 22, 200) : QColor(0, 0, 0, 200));
                painter->drawPixmap(x - IMAGE_WIDTH, 80 + (BORDER_HEIGHT + spacing) * i, IMAGE_WIDTH, BORDER_HEIGHT, QPixmap(":/images/NCHClrg.png"));
            }
        }
    }

}
QList<NchcScoreEntry> NchcScoreboardGraphic::getFridayGames() const
{
    return fridayGames;
}

void NchcScoreboardGraphic::setFridayGames(const QList<NchcScoreEntry>& value)
{
    fridayGames = value;
}
QList<NchcScoreEntry> NchcScoreboardGraphic::getSaturdayGames() const
{
    return saturdayGames;
}

void NchcScoreboardGraphic::setSaturdayGames(const QList<NchcScoreEntry>& value)
{
    saturdayGames = value;
}

void NchcScoreboardGraphic::showImg()
{
    show = true;
    scene()->update();
}

void NchcScoreboardGraphic::hide()
{
    show = false;
    scene()->update();
}



