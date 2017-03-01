#include "NchcScoreboardGraphic.h"
#include <QGraphicsScene>

#define BORDER_WIDTH 650
#define IMAGE_WIDTH 117
#define BORDER_HEIGHT 120

NchcScoreboardGraphic::NchcScoreboardGraphic() {
    setPixmap(QPixmap(":/images/Standings.png"));
    show = false;
    nchcLogo = new QPixmap(":/images/NCHClrg.png");
    *nchcLogo = nchcLogo->scaledToWidth(117, Qt::SmoothTransformation);
}

void
NchcScoreboardGraphic::paint(QPainter* painter,
                             const QStyleOptionGraphicsItem* option,
                             QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (show) {
        for (int i = x(); i < 1920; i++) {
            for (int j = y(); j < 1080; j++) {
                canvas->setPixelColor(i,j,QColor(0,0,0,0));
            }
        }
        QPainter p(canvas);
        p.translate(x(), y());
        draw(&p);
        draw(painter);
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
    if (show) {
        show = false;
        for (int i = x(); i < 1920; i++) {
            for (int j = y(); j < 1080; j++) {
                canvas->setPixelColor(i,j,QColor(0,0,0,0));
            }
        }
        scene()->update();
    }
}

void NchcScoreboardGraphic::draw(QPainter *painter)
{
    int fontSize = 28;
    painter->setFont(QFont("Arial", fontSize, QFont::Bold));
    painter->setBrush(QColor(255,255,255));
    painter->setPen(QColor(255,255,255));
    painter->drawPixmap(0, 0, this->pixmap());
    //painter->drawText(0, 0, 1920, 80, Qt::AlignCenter, "NCHC SCOREBOARD");
    painter->drawText(0, 0, 1920/2, 80, Qt::AlignCenter, leftHeader);
    painter->drawText(1920/2, 0, 1920/2, 80, Qt::AlignCenter, rightHeader);
    int spacing = (980 - (120*fridayGames.size())) / fridayGames.size();
    int x = 200;
    for (int i = 0; i < fridayGames.size(); i++) {
        // Outer border
        painter->fillRect(x, 80 + (BORDER_HEIGHT + spacing) * i, BORDER_WIDTH, BORDER_HEIGHT, fridayGames.at(i).getConfGame() ?
                              QColor(165, 0, 22, 200) : QColor(1, 1, 1, 200));
        // Inner border
        painter->fillRect(x, 80 + (BORDER_HEIGHT + spacing) * i, BORDER_WIDTH - 150, BORDER_HEIGHT, QColor(1, 1, 1));
        painter->setBrush(QColor(255,255,255));
        painter->setPen(QColor(255,255,255));
        // School
        painter->drawText(x, 80 + (BORDER_HEIGHT + spacing) * i, 500, BORDER_HEIGHT / 2, Qt::AlignLeft | Qt::AlignVCenter, fridayGames.at(i).getAway());
        painter->drawText(x,80 + (BORDER_HEIGHT + spacing) * i + BORDER_HEIGHT / 2 + 5, 500, BORDER_HEIGHT / 2 - 5, Qt::AlignLeft | Qt::AlignVCenter, fridayGames.at(i).getHome());
        QString timePd = fridayGames.at(i).getTimeAndPd();
        timePd = timePd.replace(" ", "\n");
        painter->drawText(x + BORDER_WIDTH - 150, 80 + (BORDER_HEIGHT + spacing) * i, 150, BORDER_HEIGHT, Qt::AlignCenter, timePd);

        // Score
        painter->setBrush(QColor(253,180,26));
        painter->setPen(QColor(253,180,26));
        painter->drawText(x + 500 - 60, 80 + (BORDER_HEIGHT + spacing) * i, 53, BORDER_HEIGHT / 2, Qt::AlignVCenter | Qt::AlignRight, fridayGames.at(i).getAwayScore());
        painter->drawText(x + 500 - 60, BORDER_HEIGHT / 2 + 80 + (BORDER_HEIGHT + spacing) * i + 5, 53, BORDER_HEIGHT / 2 - 5, Qt::AlignVCenter | Qt::AlignRight, fridayGames.at(i).getHomeScore());
        painter->fillRect(x, 80 + (BORDER_HEIGHT + spacing) * i + BORDER_HEIGHT / 2 - 5, BORDER_WIDTH - 150, 10, fridayGames.at(i).getConfGame() ?
                              QColor(165, 0, 22) : QColor(255, 255, 255));
        if (fridayGames.at(i).getConfGame()) {
            painter->fillRect(x - IMAGE_WIDTH, 80 + (BORDER_HEIGHT + spacing) * i, IMAGE_WIDTH, BORDER_HEIGHT, fridayGames.at(i).getConfGame() ?
                                  QColor(165, 0, 22, 200) : QColor(1, 1, 1, 150));
            painter->drawPixmap(x - IMAGE_WIDTH, 80 + (BORDER_HEIGHT + spacing) * i, IMAGE_WIDTH, BORDER_HEIGHT, *nchcLogo);
        }
    }
    x = 1120 + IMAGE_WIDTH;
    for (int i = 0; i < saturdayGames.size(); i++) {
        // Outer border
        painter->fillRect(x ,80 + (BORDER_HEIGHT + spacing) * i, BORDER_WIDTH, BORDER_HEIGHT, saturdayGames.at(i).getConfGame() ?
                              QColor(165, 0, 22, 200) : QColor(1, 1, 1, 200));
        // Inner border
        painter->fillRect(x, 80 + (BORDER_HEIGHT + spacing) * i, BORDER_WIDTH - 150, BORDER_HEIGHT, QColor(1, 1, 1));
        painter->setBrush(QColor(255,255,255));
        painter->setPen(QColor(255,255,255));
        // School
        painter->drawText(x, 80 + (BORDER_HEIGHT + spacing) * i, 500, BORDER_HEIGHT / 2, Qt::AlignLeft | Qt::AlignVCenter, saturdayGames.at(i).getAway());
        painter->drawText(x, BORDER_HEIGHT / 2 + 80 + (BORDER_HEIGHT + spacing) * i + 5, 500, BORDER_HEIGHT / 2 - 5, Qt::AlignLeft | Qt::AlignVCenter, saturdayGames.at(i).getHome());
        QString timePd = saturdayGames.at(i).getTimeAndPd();
        timePd = timePd.replace(" ", "\n");
        painter->drawText(x + BORDER_WIDTH - 150, 80 + (BORDER_HEIGHT + spacing) * i, 150, BORDER_HEIGHT, Qt::AlignCenter, timePd);

        // Score
        painter->setBrush(QColor(253,180,26));
        painter->setPen(QColor(253,180,26));
        painter->drawText(x + 500-60, 80 + (BORDER_HEIGHT + spacing) * i, 53, BORDER_HEIGHT / 2, Qt::AlignVCenter | Qt::AlignRight, saturdayGames.at(i).getAwayScore());
        painter->drawText(x + 500-60, BORDER_HEIGHT / 2 + 80 + (BORDER_HEIGHT + spacing) * i + 5, 53, BORDER_HEIGHT / 2 - 5, Qt::AlignVCenter | Qt::AlignRight, saturdayGames.at(i).getHomeScore());
        painter->fillRect(x, BORDER_HEIGHT / 2 - 5 + 80 + (BORDER_HEIGHT + spacing) * i, BORDER_WIDTH - 150, 10, saturdayGames.at(i).getConfGame() ?
                              QColor(165, 0, 22) : QColor(255, 255, 255));
        if (saturdayGames.at(i).getConfGame()) {
            painter->fillRect(x - IMAGE_WIDTH, 80 + (BORDER_HEIGHT + spacing) * i, IMAGE_WIDTH, BORDER_HEIGHT, saturdayGames.at(i).getConfGame() ?
                                  QColor(165, 0, 22, 200) : QColor(1, 1, 1, 150));
            painter->drawPixmap(x - IMAGE_WIDTH, 80 + (BORDER_HEIGHT + spacing) * i, *nchcLogo);
        }
    }

}

void NchcScoreboardGraphic::setCanvas(QImage *value)
{
    canvas = value;
}

void NchcScoreboardGraphic::setRightHeader(const QString &value)
{
    rightHeader = value.toUpper();
}

void NchcScoreboardGraphic::setLeftHeader(const QString &value)
{
    leftHeader = value.toUpper();
}



