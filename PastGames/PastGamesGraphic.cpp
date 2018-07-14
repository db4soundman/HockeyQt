#include "PastGamesGraphic.h"

#include <QFont>
#include "MiamiAllAccessHockey.h"
#include <QGraphicsScene>

#define WIDTH 760
#define HEIGHT 300
#define NAME_GRADIENT_LEVEL .3

PastGamesGraphic::PastGamesGraphic(HockeyTeam *hTeam, HockeyTeam *aTeam, QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    setRect(0,0,WIDTH,HEIGHT);
    awayTeam = aTeam;
    homeTeam = hTeam;
    border.setStart(0,0);
    border.setFinalStop(0, HEIGHT);
    border.setColorAt(0, QColor(196, 213, 242));
    border.setColorAt(1, QColor(196, 213, 242));

    background.setStart(0,0);
    background.setFinalStop(0, HEIGHT);
    background.setColorAt(0, QColor(41, 70, 91));
    background.setColorAt(1, QColor(23, 41, 53));
    //background.setColorAt(1, QColor(10,10,10));

    teamBg.setStart(0,0);
    teamBg.setFinalStop(0, 30);
    //home = hTeam;
   // away = aTeam;

    homeLogo = MiamiAllAccessHockey::homeSchool.getLogo().scaledToHeight(30, Qt::SmoothTransformation);
    awayLogo = MiamiAllAccessHockey::awaySchool.getLogo().scaledToHeight(30, Qt::SmoothTransformation);
    homeColor = MiamiAllAccessHockey::homeSchool.getPrimaryColor();
    awayColor = MiamiAllAccessHockey::awaySchool.getPrimaryColor();
    homeName = MiamiAllAccessHockey::homeSchool.getFullName();
    awayName = MiamiAllAccessHockey::awaySchool.getFullName();
    awayHistory = aTeam->getGameHistory();
    homeHistory = hTeam->getGameHistory();
    numToShow = 0;
    show = false;

    isHomeTeam = true;

    connect(awayTeam, SIGNAL(rosterChanged()), this, SLOT(updateAwayHistory()));
    connect(homeTeam, SIGNAL(rosterChanged()), this, SLOT(updateHomeHistory()));
}

void PastGamesGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (show) {
        QRectF graphicRect = rect();
//        if (!seriesMode) {
//            graphicRect.setWidth(520);
//        }
        graphicRect.setHeight(30 * (numToShow+1) + 30);
        painter->fillRect(graphicRect, border);
        painter->fillRect(4,4, graphicRect.width()-8, graphicRect.height()-8, background);
        painter->fillRect(0,0, graphicRect.width(), 30, teamBg);
        painter->drawPixmap(0,0, isHomeTeam ? homeLogo : awayLogo);
        QFont headerFont("Arial", 20, QFont::Bold);
        painter->setFont(headerFont);
        painter->setPen(QColor(255,255,255));
        painter->drawText(0,0,graphicRect.width(),30, Qt::AlignCenter, isHomeTeam ? homeName : awayName);
        painter->setPen(QColor(1,1,1));
        painter->fillRect(0,30, graphicRect.width(), 20, border);
        QFont font("Arial", 16, QFont::Bold);
        painter->setFont(font);
        painter->drawText(0,30, graphicRect.width(), 20, Qt::AlignCenter, "RECENT GAMES");

        painter->setPen(QColor(255,255,255));
        for (int i = gameHistory.size() - numToShow, x = 0; x < numToShow; i++, x++) {
            int y = 30 * (x+1) + 30;
            painter->drawText(15, y, 120, 30, 0, gameHistory[i].getDate());
            painter->drawText(140,y, 40, 30, 0, gameHistory[i].getHome() ? "VS" : "AT");
            painter->drawText(180,y, 300, 30, 0, gameHistory[i].getOpponent());
            QString result = "T";
            if (gameHistory[i].getOurScore() > gameHistory[i].getTheirScore()) {
                result = "W";
            } else if (gameHistory[i].getOurScore() < gameHistory[i].getTheirScore()) {
                result = "L";
            }
            painter->drawText(480, y, 80, 30, 0, result);
            painter->drawText(560, y, 100, 30, 0, gameHistory[i].getOurScore() + "-" + gameHistory[i].getTheirScore());
            painter->drawText(660, y, 100, 30, 0, gameHistory[i].getPeriods());
        }
    }
}

void PastGamesGraphic::toggleShow()
{
    show = true;
    emit addNoTransparencyZone(QRect(x(), y(), WIDTH, 30));
    scene()->update(x(), y(), WIDTH, HEIGHT);
}

void PastGamesGraphic::hide()
{
    if (show) {
        show = false;
        emit removeNoTransparencyZone(QRect(x(), y(), WIDTH, 30));
        scene()->update(x(), y(), WIDTH, HEIGHT);
    }
}

void PastGamesGraphic::receiveData(bool team, int num)
{
    //gameHistory=sched;
    isHomeTeam = team;
    QColor color = isHomeTeam ? homeColor:awayColor;
    int red, green, blue;
    red = -1*color.red() *NAME_GRADIENT_LEVEL + color.red();
    green = -1*color.green() *NAME_GRADIENT_LEVEL + color.green();
    blue = -1*color.blue() *NAME_GRADIENT_LEVEL + color.blue();

    QColor end(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);

    teamBg.setColorAt(0, color);
    teamBg.setColorAt(1, end);
    numToShow = num;
    gameHistory = isHomeTeam ? homeHistory : awayHistory;

    toggleShow();
}

void PastGamesGraphic::updateAwayHistory()
{
    awayHistory = awayTeam->getGameHistory();
}

void PastGamesGraphic::updateHomeHistory()
{
    homeHistory= homeTeam->getGameHistory();
}
