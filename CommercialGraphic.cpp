#include "CommercialGraphic.h"
#include <QFontMetrics>
#include <QGraphicsScene>
#include "GraphicChooser.txt"

#ifdef GRADIENT_LOOK
//#define WIDTH 1920/2
//#define NAME_WIDTH 860
#define RECT_HEIGHT 120
#define CENTER_OFFSET 100
#define BLACK_BAR_HEIGHT 60
#define GRADIENT_LEVEL .5
#define SHOW_CLOCK 0
#define INTERMISSION 1
#define FINAL 2

CommercialGraphic::CommercialGraphic(HockeyGame* game, int width, QString pawayLogo, QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent), blackBar(QPixmap(":/images/ppBar.png")),
    homeLogo(QPixmap(":/images/M.png")) {
    hockeyGame = game;
    show = false;
    WIDTH = width / 2;
    NAME_WIDTH = WIDTH - 100;
    inGame  = false;
    QFont font("Arial", 60, QFont::Bold);
    QFont sponsorFont("Arial", 36, QFont::Bold);
#ifdef Q_OS_OSX
    font.setPointSize(68);
    sponsorFont.setPointSize(44);
#endif
    //QPixmap pix(pawayLogo);
    away = new QGraphicsTextItem(game->getAwayName());
    away->setFont(font);
    checkAwayFont();
    home = new QGraphicsTextItem(game->getHomeName());
    home->setFont(font);

    descriptiveFont = sponsorFont;
    prepareGradients(game->getAwayColor(), game->getHomeColor());
    networkText = "NCHC.tv";
    clockStatus = SHOW_CLOCK;
    connect(game->getGameClock(), SIGNAL(clockUpdated()), this, SLOT(updateClock()));
    awayLogo = new QPixmap(pawayLogo);
    if (awayLogo->height() > 120) {
        *awayLogo = awayLogo->scaledToHeight(120, Qt::SmoothTransformation);
    }
  /*  if (awayLogo->width() > 1919) {
       *awayLogo =  awayLogo->scaledToWidth(800, Qt::SmoothTransformation);
    }*/
   homeLogo = homeLogo.scaledToHeight(120, Qt::SmoothTransformation);
}

void CommercialGraphic::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                              QWidget* widget) {
    if (show){
        painter->setPen(QColor(255, 255, 255));
        painter->drawPixmap(WIDTH/2, -BLACK_BAR_HEIGHT, WIDTH, BLACK_BAR_HEIGHT, blackBar);

        painter->setFont(descriptiveFont);
        painter->drawText(WIDTH / 2, -BLACK_BAR_HEIGHT, WIDTH, BLACK_BAR_HEIGHT, Qt::AlignCenter, networkText);

        painter->fillRect(0, 0, WIDTH, RECT_HEIGHT, awayTeamGradient);
        painter->fillRect(WIDTH, 0, WIDTH, RECT_HEIGHT, homeTeamGradient);
       // painter->setFont(away->font());
        //painter->drawText(10, 0, NAME_WIDTH, RECT_HEIGHT, Qt::AlignCenter, away->toPlainText());
        //painter->drawPixmap(WIDTH - CENTER_OFFSET - 100 - awayLogo.width(), 20, awayLogo);

        painter->setOpacity(.996);
        painter->drawPixmap(WIDTH - CENTER_OFFSET - 100 - awayLogo->width(), 0, *awayLogo);

        painter->setFont(home->font());
        //painter->drawText(WIDTH + CENTER_OFFSET, 0, NAME_WIDTH, RECT_HEIGHT, Qt::AlignCenter, home->toPlainText());
        painter->drawPixmap(WIDTH + CENTER_OFFSET + 100, 0, homeLogo);
        painter->fillRect(WIDTH - CENTER_OFFSET, 0, CENTER_OFFSET * 2, RECT_HEIGHT, QColor(0,0,0, 100));
        painter->setOpacity(1);
        painter->drawText(WIDTH - CENTER_OFFSET, 0, CENTER_OFFSET, RECT_HEIGHT, Qt::AlignCenter, awayScore);
        painter->drawText(WIDTH, 0, CENTER_OFFSET, RECT_HEIGHT, Qt::AlignCenter, homeScore);


        painter->drawPixmap(WIDTH - 200, RECT_HEIGHT, WIDTH - (WIDTH- 400), BLACK_BAR_HEIGHT, blackBar);
        painter->setFont(descriptiveFont);
        if (clockStatus == FINAL) {
            painter->drawText(WIDTH - 200, RECT_HEIGHT, WIDTH - (WIDTH- 400), BLACK_BAR_HEIGHT, Qt::AlignCenter, "FINAL");
        }
        else {
            painter->drawText(WIDTH- 190, RECT_HEIGHT, WIDTH - (WIDTH- 400), BLACK_BAR_HEIGHT, Qt::AlignLeft, period);
            painter->drawText(WIDTH-200, RECT_HEIGHT, WIDTH - (WIDTH- 390), BLACK_BAR_HEIGHT, Qt::AlignRight, clock);
        }
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
    scene()->update();
}

void CommercialGraphic::updateClock()
{
    if (show) {
        if (clockStatus == SHOW_CLOCK) {
            if (useClock) {
            clock = hockeyGame->getGameClock()->toString();
            }
            else {
                clock = "PERIOD";
            }
        }
        else if (clockStatus == INTERMISSION) {
            clock = "INT";
        }
        else {
            clock = "FINAL";
        }


    }
}

void CommercialGraphic::showClock() {
    clockStatus = SHOW_CLOCK;
    updateClock();
    if (show)
        scene()->update(x() + WIDTH - 200, y() + RECT_HEIGHT, WIDTH - (WIDTH- 400), BLACK_BAR_HEIGHT);
}

void CommercialGraphic::intermissionTime()
{
    clockStatus = INTERMISSION;
    updateClock();
    if (show)
        scene()->update(x() + WIDTH - 200, y() + RECT_HEIGHT, WIDTH - (WIDTH- 400), BLACK_BAR_HEIGHT);
}

void CommercialGraphic::finalTime()
{
    clockStatus = FINAL;
    updateClock();
    if (show)
        scene()->update(x() + WIDTH - 200, y() + RECT_HEIGHT, WIDTH - (WIDTH- 400), BLACK_BAR_HEIGHT);
}

void CommercialGraphic::hide()
{
    if (show) {
        show = false;
        scene()->update();
    }
}

void CommercialGraphic::checkAwayFont()
{
    int fontPointSize = away->font().pointSize();
    int subtraction = 1;
    QFontMetrics fontSize(away->font());
    while (fontSize.width(away->toPlainText()) > NAME_WIDTH) {
        QFont tempFont("Arial", fontPointSize - subtraction, QFont::Bold);
        subtraction++;
        away->setFont(tempFont);
        QFontMetrics temp(away->font());
        fontSize = temp;
    }
}

void CommercialGraphic::prepareGradients(QColor awayColor, QColor homeColor)
{
    homeTeamGradient.setStart(0, 0);
    homeTeamGradient.setFinalStop(0, 120);
    awayTeamGradient.setStart(0,0);
    awayTeamGradient.setFinalStop(0, 120);
    int red, green, blue;
    red = -1*homeColor.red() *GRADIENT_LEVEL + homeColor.red();
    green = -1*homeColor.green() *GRADIENT_LEVEL + homeColor.green();
    blue = -1*homeColor.blue() *GRADIENT_LEVEL + homeColor.blue();

    QColor end(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    homeTeamGradient.setColorAt(.4, homeColor);
    homeTeamGradient.setColorAt(.6, homeColor);
    homeTeamGradient.setColorAt(1, end);
    homeTeamGradient.setColorAt(0, end);

    red = -1*awayColor.red() *GRADIENT_LEVEL + awayColor.red();
    green = -1*awayColor.green() *GRADIENT_LEVEL + awayColor.green();
    blue = -1*awayColor.blue() *GRADIENT_LEVEL + awayColor.blue();
    QColor end2(red, green, blue);
    if (end2 == QColor(0,0,0))
        end2 = QColor(1,1,1);
    awayTeamGradient.setColorAt(.4, awayColor);
    awayTeamGradient.setColorAt(.6, awayColor);
    awayTeamGradient.setColorAt(1, end2);
    awayTeamGradient.setColorAt(0, end2);
}
#else
#include "CommercialGraphic.h"
#include <QFontMetrics>
#include <QGraphicsScene>

#define NAME_WIDTH 400
#define RECT_HEIGHT 50
#define BLACK_BAR_HEIGHT 30
#define GRADIENT_LEVEL .1
#define GRAPHIC_WIDTH 600
#define CLOCK_WIDTH 200
#define SHOW_CLOCK 0
#define INTERMISSION 1
#define FINAL 2
#define AWAY_Y 4
#define HOME_Y (AWAY_Y * 2 + RECT_HEIGHT - 1)

CommercialGraphic::CommercialGraphic(HockeyGame* game, QPixmap pawayLogo, QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent), blackBar(QPixmap(":/images/ppBar.png")),
    homeLogo(QPixmap(":/images/M.png")) {
    setPixmap(QPixmap(":/images/Standings.png"));
    useClock = true;
    hockeyGame = game;
    show = false;
    inGame  = false;
    QFont font("Arial", 34, QFont::Bold);
    QFont sponsorFont("Arial", 26, QFont::Bold);
#ifdef Q_OS_OSX
    font.setPointSize(38);
    sponsorFont.setPointSize(14);
#endif
    //QPixmap pix(pawayLogo);
    away = new QGraphicsTextItem(game->getAwayName());
    away->setFont(font);
    checkAwayFont();
    home = new QGraphicsTextItem(game->getHomeName());
    home->setFont(font);

    descriptiveFont = sponsorFont;
    prepareGradients(game->getAwayColor(), game->getHomeColor());
    networkText = "NCHC.tv";
    clockStatus = SHOW_CLOCK;
    connect(game->getGameClock(), SIGNAL(clockUpdated()), this, SLOT(updateClock()));
    awayLogo = new QPixmap(pawayLogo);
    if (awayLogo->height() > RECT_HEIGHT) {
        *awayLogo = awayLogo->scaledToHeight(RECT_HEIGHT, Qt::SmoothTransformation);
    }
  /*  if (awayLogo->width() > 1919) {
       *awayLogo =  awayLogo->scaledToWidth(800, Qt::SmoothTransformation);
    }*/
   homeLogo = homeLogo.scaledToHeight(RECT_HEIGHT, Qt::SmoothTransformation);
}

void CommercialGraphic::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                              QWidget* widget) {
    if (show){
        painter->fillRect(-10, 0, GRAPHIC_WIDTH + 210, RECT_HEIGHT * 2 + 11, bgGradient);
        painter->setPen(QColor(255, 255, 255));
        //painter->drawPixmap(WIDTH/2, -BLACK_BAR_HEIGHT, WIDTH, BLACK_BAR_HEIGHT, blackBar);
        painter->fillRect(0, -BLACK_BAR_HEIGHT, GRAPHIC_WIDTH - 200, BLACK_BAR_HEIGHT, QColor(20,20,20));
        //painter->fillRect(0, RECT_HEIGHT * 2, GRAPHIC_WIDTH, BLACK_BAR_HEIGHT, clockGradient);
        painter->setFont(descriptiveFont);
        painter->drawText(0, -BLACK_BAR_HEIGHT, GRAPHIC_WIDTH - 200, BLACK_BAR_HEIGHT, Qt::AlignCenter, networkText);

        painter->fillRect(0, AWAY_Y, GRAPHIC_WIDTH, RECT_HEIGHT, awayTeamGradient);
        //painter->drawRect(0,0,GRAPHIC_WIDTH,RECT_HEIGHT,);
        painter->fillRect(0, HOME_Y, GRAPHIC_WIDTH, RECT_HEIGHT, homeTeamGradient);
        painter->setOpacity(.996);
        painter->drawPixmap(5, AWAY_Y, *awayLogo);
        painter->drawPixmap(5, HOME_Y, homeLogo);
        painter->setFont(away->font());
        painter->setOpacity(1);
        painter->drawText(100, AWAY_Y, NAME_WIDTH, RECT_HEIGHT, Qt::AlignVCenter, away->toPlainText());
        painter->setFont(home->font());
        painter->drawText(100, HOME_Y, NAME_WIDTH, RECT_HEIGHT, Qt::AlignVCenter, home->toPlainText());
        painter->drawText(GRAPHIC_WIDTH - 100, AWAY_Y, 100, RECT_HEIGHT, Qt::AlignCenter, awayScore);
        painter->drawText(GRAPHIC_WIDTH - 100, HOME_Y, 100, RECT_HEIGHT, Qt::AlignCenter, homeScore);


        //painter->drawPixmap(WIDTH - 200, RECT_HEIGHT, WIDTH - (WIDTH- 400), BLACK_BAR_HEIGHT, blackBar);
        painter->setFont(descriptiveFont);
        if (clockStatus == FINAL || period == "SHOOTOUT") {
            painter->drawText(GRAPHIC_WIDTH,0, CLOCK_WIDTH, RECT_HEIGHT * 2 + 10, Qt::AlignCenter, clockStatus == FINAL ? "FINAL" : period);
        }
        else {
            painter->drawText(GRAPHIC_WIDTH, 0, CLOCK_WIDTH, RECT_HEIGHT + 5, Qt::AlignCenter, period);
            painter->drawText(GRAPHIC_WIDTH, RECT_HEIGHT, CLOCK_WIDTH, RECT_HEIGHT + 5, Qt::AlignCenter, clock);
        }
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
    checkAwayFont();
    scene()->update();
}

void CommercialGraphic::updateClock()
{
    if (show) {
        if (clockStatus == SHOW_CLOCK) {
            if (useClock) {
            clock = hockeyGame->getGameClock()->toString();
            }
            else {
                clock = "PERIOD";
            }
            scene()->update(x() + GRAPHIC_WIDTH, y(), CLOCK_WIDTH, RECT_HEIGHT*2);
        }
        else if (clockStatus == INTERMISSION) {
            clock = "INT";
        }
        else {
            clock = "FINAL";
        }
    }
}

void CommercialGraphic::showClock() {
    clockStatus = SHOW_CLOCK;
    updateClock();
    if (show)
        scene()->update(x()+ GRAPHIC_WIDTH, y(), CLOCK_WIDTH, RECT_HEIGHT*2);
}

void CommercialGraphic::intermissionTime()
{
    clockStatus = INTERMISSION;
    updateClock();
    if (show)
        scene()->update(x()+ GRAPHIC_WIDTH, y(), CLOCK_WIDTH, RECT_HEIGHT*2);
}

void CommercialGraphic::finalTime()
{
    clockStatus = FINAL;
    updateClock();
    if (show)
        scene()->update(x()+ GRAPHIC_WIDTH, y(), CLOCK_WIDTH, RECT_HEIGHT*2 + 10);
}

void CommercialGraphic::hide()
{
    if (show) {
        show = false;
        scene()->update();
    }
}

void CommercialGraphic::checkAwayFont()
{
    int fontPointSize = away->font().pointSize();
    int subtraction = 1;
    QFontMetrics fontSize(away->font());
    while (fontSize.width(away->toPlainText()) > NAME_WIDTH) {
        QFont tempFont("Arial", fontPointSize - subtraction, QFont::Bold);
        subtraction++;
        away->setFont(tempFont);
        QFontMetrics temp(away->font());
        fontSize = temp;
    }
}

void CommercialGraphic::prepareGradients(QColor awayColor, QColor homeColor)
{
    homeTeamGradient.setStart(0, 0);
    homeTeamGradient.setFinalStop(0, RECT_HEIGHT);
    awayTeamGradient.setStart(0,RECT_HEIGHT);
    awayTeamGradient.setFinalStop(0, RECT_HEIGHT*2);
    int red, green, blue;
    red = -1*homeColor.red() *GRADIENT_LEVEL + homeColor.red();
    green = -1*homeColor.green() *GRADIENT_LEVEL + homeColor.green();
    blue = -1*homeColor.blue() *GRADIENT_LEVEL + homeColor.blue();

    QColor end(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    homeTeamGradient.setColorAt(.4, homeColor);
    homeTeamGradient.setColorAt(.6, homeColor);
    homeTeamGradient.setColorAt(1, end);
    homeTeamGradient.setColorAt(0, end);

    red = -1*awayColor.red() *GRADIENT_LEVEL + awayColor.red();
    green = -1*awayColor.green() *GRADIENT_LEVEL + awayColor.green();
    blue = -1*awayColor.blue() *GRADIENT_LEVEL + awayColor.blue();
    QColor end2(red, green, blue);
    if (end2 == QColor(0,0,0))
        end2 = QColor(1,1,1);
    awayTeamGradient.setColorAt(.4, awayColor);
    awayTeamGradient.setColorAt(.6, awayColor);
    awayTeamGradient.setColorAt(1, end2);
    awayTeamGradient.setColorAt(0, end2);


    clockGradient.setStart(0, RECT_HEIGHT*2);
    clockGradient.setFinalStop(0, RECT_HEIGHT*2  + BLACK_BAR_HEIGHT);
    QColor sbRed(156,0,0);
    red = -1*sbRed.red() *GRADIENT_LEVEL + sbRed.red();
    green = -1*sbRed.green() *GRADIENT_LEVEL + sbRed.green();
    blue = -1*sbRed.blue() *GRADIENT_LEVEL + sbRed.blue();

    QColor end3(red, green, blue);
    if (end3 == QColor(0,0,0))
        end3 = QColor(1,1,1);
    clockGradient.setColorAt(0, end3);
    clockGradient.setColorAt(1, sbRed);

    bgGradient.setStart(-10,0);
    bgGradient.setFinalStop(-10, RECT_HEIGHT * 2 + BLACK_BAR_HEIGHT+10);
    bgGradient.setColorAt(0, QColor(1,1,1));
    bgGradient.setColorAt(1, QColor(1,1,1));
    bgGradient.setColorAt(.5, QColor(50,50,50));
}
#endif

void CommercialGraphic::changeUseClock(bool uc)
{
    useClock = uc;
    if (show) {
        updateClock();
    }
}
