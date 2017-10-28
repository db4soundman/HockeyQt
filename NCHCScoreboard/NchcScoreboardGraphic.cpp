#include "NchcScoreboardGraphic.h"
#include <QGraphicsScene>

#define WIDTH 1920
#define HEIGHT 1080

#define BORDER_WIDTH 550
#define BORDER_HEIGHT 81

NchcScoreboardGraphic::NchcScoreboardGraphic() {

    setRect(0,0,WIDTH,HEIGHT);
    show = false;
    nchcLogo = new QPixmap(":/images/NCHClrg.png");
    *nchcLogo = nchcLogo->scaledToHeight(BORDER_HEIGHT, Qt::SmoothTransformation);
    mainGradient.setStart(0,0);
    mainGradient.setFinalStop(0,HEIGHT);
    mainGradient.setColorAt(0, QColor(41, 70, 91));
    mainGradient.setColorAt(1, QColor(41, 70, 91));
    //mainGradient.setColorAt(1, QColor(23, 41, 53));
}

void
NchcScoreboardGraphic::paint(QPainter* painter,
                             const QStyleOptionGraphicsItem* option,
                             QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (show) {
        int fontSize = 20;
#ifdef Q_OS_OSX
        fontSize = 40;
#endif
        painter->setFont(QFont("Arial", fontSize, QFont::Bold));

        painter->setPen(QColor(255,255,255));
        painter->fillRect(rect(),mainGradient);
        //painter->drawText(0, 0, 1920, 80, Qt::AlignCenter, "NCHC SCOREBOARD");
        painter->drawText(0, 0, 1920/2, 80, Qt::AlignCenter, leftHeader);
        painter->drawText(1920/2, 0, 1920/2, 80, Qt::AlignCenter, rightHeader);
        int IMAGE_WIDTH = nchcLogo->width();
        int spacing = (980 - (80*fridayGames.size())) / fridayGames.size();
        int x = 200;
        for (int i = 0; i < fridayGames.size(); i++) {


            painter->setPen(QColor(196, 213, 242,0));
            painter->setBrush(QColor(30,50,65));
            // Outer border
            painter->drawRect(x, 80 + (BORDER_HEIGHT + spacing) * i, BORDER_WIDTH, BORDER_HEIGHT);
            // Inner border
            painter->setPen(QColor(196, 213, 242));
            painter->setBrush(QColor(30,50,65,0));
            painter->drawRect(x+BORDER_WIDTH - 150, 80 + (BORDER_HEIGHT + spacing) * i, 1, BORDER_HEIGHT);
            painter->setPen(QColor(255,255,255));

            // School
            painter->drawText(x, 80 + (BORDER_HEIGHT + spacing) * i, 500, BORDER_HEIGHT / 2, Qt::AlignLeft | Qt::AlignVCenter, fridayGames.at(i).getAway());
            painter->drawText(x,80 + (BORDER_HEIGHT + spacing) * i + BORDER_HEIGHT / 2  +1, 500, BORDER_HEIGHT / 2, Qt::AlignLeft | Qt::AlignVCenter, fridayGames.at(i).getHome());
            QString timePd = fridayGames.at(i).getTimeAndPd();
            timePd = timePd.replace(" ", "\n");
            painter->drawText(x + BORDER_WIDTH - 150, 80 + (BORDER_HEIGHT + spacing) * i, 150, BORDER_HEIGHT, Qt::AlignCenter, timePd);

            // Score
           //painter->setBrush(QColor(253,180,26));
            painter->setPen(QColor(253,180,26));
            painter->drawText(x + BORDER_WIDTH - 150 - 60, 80 + (BORDER_HEIGHT + spacing) * i, 53, BORDER_HEIGHT / 2, Qt::AlignVCenter | Qt::AlignRight, fridayGames.at(i).getAwayScore());
            painter->drawText(x + BORDER_WIDTH - 150 - 60, 80 + (BORDER_HEIGHT + spacing) * i + BORDER_HEIGHT / 2 +1 , 53, BORDER_HEIGHT / 2, Qt::AlignVCenter | Qt::AlignRight, fridayGames.at(i).getHomeScore());
            painter->setPen(QColor(196, 213, 242));
            painter->drawRect(x, 80 + (BORDER_HEIGHT + spacing) * i + BORDER_HEIGHT / 2, BORDER_WIDTH - 150, 1);
            if (fridayGames.at(i).getConfGame()) {
                painter->fillRect(x - IMAGE_WIDTH, 80 + (BORDER_HEIGHT + spacing) * i, IMAGE_WIDTH, BORDER_HEIGHT, fridayGames.at(i).getConfGame() ?
                                      QColor(165, 0, 22, 200) : QColor(1, 1, 1, 150));
                painter->drawPixmap(x - IMAGE_WIDTH, 80 + (BORDER_HEIGHT + spacing) * i, *nchcLogo);
            }
        }
        x = 1120 + IMAGE_WIDTH;
        for (int i = 0; i < saturdayGames.size(); i++) {
            painter->setPen(QColor(196, 213, 242,0));
            painter->setBrush(QColor(30,50,65));
            // Outer border
            painter->drawRect(x, 80 + (BORDER_HEIGHT + spacing) * i, BORDER_WIDTH, BORDER_HEIGHT);
            // Inner border
            painter->setPen(QColor(196, 213, 242));
            painter->setBrush(QColor(30,50,65,0));
            painter->drawRect(x+BORDER_WIDTH - 150, 80 + (BORDER_HEIGHT + spacing) * i, 1, BORDER_HEIGHT);
            painter->setPen(QColor(255,255,255));

            // School
            painter->drawText(x, 80 + (BORDER_HEIGHT + spacing) * i, 500, BORDER_HEIGHT / 2, Qt::AlignLeft | Qt::AlignVCenter, saturdayGames.at(i).getAway());
            painter->drawText(x,80 + (BORDER_HEIGHT + spacing) * i + BORDER_HEIGHT / 2  +1, 500, BORDER_HEIGHT / 2, Qt::AlignLeft | Qt::AlignVCenter, saturdayGames.at(i).getHome());
            QString timePd = saturdayGames.at(i).getTimeAndPd();
            timePd = timePd.replace(" ", "\n");
            painter->drawText(x + BORDER_WIDTH - 150, 80 + (BORDER_HEIGHT + spacing) * i, 150, BORDER_HEIGHT, Qt::AlignCenter, timePd);

            // Score
           //painter->setBrush(QColor(253,180,26));
            painter->setPen(QColor(253,180,26));
            painter->drawText(x + BORDER_WIDTH - 150 - 60, 80 + (BORDER_HEIGHT + spacing) * i, 53, BORDER_HEIGHT / 2, Qt::AlignVCenter | Qt::AlignRight, saturdayGames.at(i).getAwayScore());
            painter->drawText(x + BORDER_WIDTH - 150 - 60, 80 + (BORDER_HEIGHT + spacing) * i + BORDER_HEIGHT / 2 +1 , 53, BORDER_HEIGHT / 2, Qt::AlignVCenter | Qt::AlignRight, saturdayGames.at(i).getHomeScore());
            painter->setPen(QColor(196, 213, 242));
            painter->drawRect(x, 80 + (BORDER_HEIGHT + spacing) * i + BORDER_HEIGHT / 2, BORDER_WIDTH - 150, 1);
            if (saturdayGames.at(i).getConfGame()) {
                painter->fillRect(x - IMAGE_WIDTH, 80 + (BORDER_HEIGHT + spacing) * i, IMAGE_WIDTH, BORDER_HEIGHT, saturdayGames.at(i).getConfGame() ?
                                      QColor(165, 0, 22, 200) : QColor(1, 1, 1, 150));
                painter->drawPixmap(x - IMAGE_WIDTH, 80 + (BORDER_HEIGHT + spacing) * i, *nchcLogo);
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
    if (show) {
        show = false;
        scene()->update();
    }
}

void NchcScoreboardGraphic::setRightHeader(const QString &value)
{
    rightHeader = value.toUpper();
}

void NchcScoreboardGraphic::setLeftHeader(const QString &value)
{
    leftHeader = value.toUpper();
}



