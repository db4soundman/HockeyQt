#include "CommercialGraphic.h"
#include <QFontMetrics>
#include <QGraphicsScene>

#define WIDTH 1000
#define NAME_WIDTH 900
#define GRADIENT_LEVEL .5
#define SHOW_CLOCK 0
#define INTERMISSION 1
#define FINAL 2

CommercialGraphic::CommercialGraphic(HockeyGame* game, QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent), blackBar(QPixmap(":/images/ppBar.png")) {
    hockeyGame = game;
    show = inGame  = false;
    QFont font("Arial", 38, QFont::Bold);
    QFont sponsorFont("Arial", 36, QFont::Bold);
#ifdef Q_OS_OSX
    font.setPointSize(44);
    sponsorFont.setPointSize(40);
    #endif

    away = new QGraphicsTextItem(game->getAwayName());
    away->setFont(font);
    checkAwayFont();
    home = new QGraphicsTextItem(game->getHomeName());
    home->setFont(font);

    descriptiveFont = sponsorFont;
    prepareGradients(game->getAwayColor(), game->getHomeColor());
    maaText = "Miami All-Access";
    clockStatus = SHOW_CLOCK;
    connect(game->getGameClock(), SIGNAL(clockUpdated()), this, SLOT(updateClock()));
}

void CommercialGraphic::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                              QWidget* widget) {
    painter->drawPixmap(0, -46, WIDTH, 46, blackBar);
    painter->setPen(QColor(255, 255, 255));
    painter->setFont(descriptiveFont);
    painter->drawText(0, -46, WIDTH, 46, Qt::AlignCenter, maaText);
    painter->fillRect(0, 0, WIDTH, 60, awayTeamGradient);
    painter->fillRect(0, 60, WIDTH, 60, homeTeamGradient);
    painter->setFont(away->font());
    painter->drawText(10, 0, NAME_WIDTH, 60, Qt::AlignLeft | Qt::AlignVCenter, away->toPlainText());
    painter->setFont(home->font());
    painter->drawText(10, 60, NAME_WIDTH, 60, Qt::AlignLeft | Qt::AlignVCenter, home->toPlainText());
    painter->drawText(NAME_WIDTH, 0, WIDTH - NAME_WIDTH, 60, Qt::AlignCenter, awayScore);
    painter->drawText(NAME_WIDTH, 60, WIDTH - NAME_WIDTH, 60, Qt::AlignCenter, homeScore);
    painter->drawPixmap(WIDTH - 400, 120, WIDTH - (WIDTH- 400), 46, blackBar);
    painter->setFont(descriptiveFont);
    if (clockStatus == FINAL) {
        painter->drawText(WIDTH - 400, 120, WIDTH - (WIDTH- 400), 46, Qt::AlignCenter, "FINAL");
    }
    else {
        painter->drawText(WIDTH-410, 120, 200, 46, Qt::AlignLeft, period);
        painter->drawText(WIDTH-410, 120, 190, 46, Qt::AlignRight, clock);
    }
}

void CommercialGraphic::prepareAndShow()
{
    awayScore = QString::number(hockeyGame->getAwayScore());
    homeScore = QString::number(hockeyGame->getHomeScore());

    switch (hockeyGame->getPeriod()) {
    case 0:
        inGame = false;
        period = "Starts in";
        break;
    case 1:
        inGame = true;
        period = "1st";
        break;
    case 2:
        period = "2nd";
        break;
    case 3:
        period = "3rd";
        break;
    case 4:
        period = "OT";
        break;
    case 5:
        period = "SHOOTOUT";
        break;
    default:
        period = "";
        break;
    }
    show = true;
    updateClock();
}

void CommercialGraphic::updateClock()
{
    if (show) {
        if (clockStatus == SHOW_CLOCK) {
            clock = hockeyGame->getGameClock()->toString();
        }
        else if (clockStatus == INTERMISSION) {
            clock = "INT";
        }
        else {
            clock = "FINAL";
        }

        scene()->update();
    }
}

void CommercialGraphic::showClock() {
    clockStatus = SHOW_CLOCK;
}

void CommercialGraphic::intermissionTime()
{
    clockStatus = INTERMISSION;
}

void CommercialGraphic::finalTime()
{
    clockStatus = FINAL;
}

void CommercialGraphic::hide()
{
    show = false;
}

void CommercialGraphic::checkAwayFont()
{
    int fontPointSize = away->font().pointSize();
    int subtraction = 1;
    QFontMetrics fontSize(away->font());
    while (fontSize.width(away->toPlainText()) > NAME_WIDTH - 10) {
        QFont tempFont("Arial", fontPointSize - subtraction, QFont::Bold);
        subtraction++;
        away->setFont(tempFont);
        QFontMetrics temp(away->font());
        fontSize = temp;
    }
}

void CommercialGraphic::prepareGradients(QColor awayColor, QColor homeColor)
{
    homeTeamGradient.setStart(0, 60);
    homeTeamGradient.setFinalStop(0, 120);
    awayTeamGradient.setStart(0,0);
    awayTeamGradient.setFinalStop(0,60);
    int red, green, blue;
    red = -1*homeColor.red() *GRADIENT_LEVEL + homeColor.red();
    green = -1*homeColor.green() *GRADIENT_LEVEL + homeColor.green();
    blue = -1*homeColor.blue() *GRADIENT_LEVEL + homeColor.blue();

    QColor end(red, green, blue);
    homeTeamGradient.setColorAt(.4, homeColor);
    homeTeamGradient.setColorAt(.6, homeColor);
    homeTeamGradient.setColorAt(1, end);
    homeTeamGradient.setColorAt(0, end);

    red = -1*awayColor.red() *GRADIENT_LEVEL + awayColor.red();
    green = -1*awayColor.green() *GRADIENT_LEVEL + awayColor.green();
    blue = -1*awayColor.blue() *GRADIENT_LEVEL + awayColor.blue();
    QColor end2(red, green, blue);
    awayTeamGradient.setColorAt(.4, awayColor);
    awayTeamGradient.setColorAt(.6, awayColor);
    awayTeamGradient.setColorAt(1, end2);
    awayTeamGradient.setColorAt(0, end2);
}
