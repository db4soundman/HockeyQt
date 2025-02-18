#include "CommercialGraphic.h"
#include <QFontMetrics>
#include <QGraphicsScene>
#include "GraphicChooser.txt"
#include <QGraphicsScene>
#include "MiamiAllAccessHockey.h"
#include "globals.h"

#define NAME_WIDTH 290
#define RECT_HEIGHT 180
#define LOGO_HEIGHT 130
#define BLACK_BAR_HEIGHT 30
#define GRADIENT_LEVEL .4
#define GRAPHIC_WIDTH 1100
#define CLOCK_X 400
#define CLOCK_WIDTH 300
#define SHOW_CLOCK 0
#define INTERMISSION 1
#define FINAL 2
#define AWAY_Y 4
#define HOME_Y (AWAY_Y * 2 + RECT_HEIGHT - 1)
#define GRAPHIC_HEIGHT 200
#define BORDER_THICKNESS 10
#define SCORE_WIDTH 100

CommercialGraphic::CommercialGraphic(HockeyGame* game,QGraphicsItem* parent) :
    QGraphicsRectItem(parent), homeLogo(MiamiAllAccessHockey::homeSchool.getLogo()) {
    setRect(0,0,GRAPHIC_WIDTH, GRAPHIC_HEIGHT);
    useClock = true;
    hockeyGame = game;
    show = false;
    inGame  = false;
    QFont font("Arial", 34, QFont::Bold);
    QFont sponsorFont("Arial", 24, QFont::Bold);
#ifdef Q_OS_OSX
    font.setPointSize(38);
    sponsorFont.setPointSize(14);
#endif
    //QPixmap pix(pawayLogo);
    networkLogo =Globals::networkLogoPath.contains("ims images",Qt::CaseInsensitive) ?
                MiamiAllAccessHockey::getImgFromESPN(Globals::networkLogoPath,90, CLOCK_WIDTH-40) :
                MiamiAllAccessHockey::getImgFromResources(Globals::networkLogoPath,90, CLOCK_WIDTH-40);
    away = new QGraphicsTextItem(MiamiAllAccessHockey::awaySchool.getFullName());
    away->setFont(font);
    checkAwayFont();
    home = new QGraphicsTextItem(MiamiAllAccessHockey::homeSchool.getFullName());
    home->setFont(font);
    altAwayLogoBg = false;
    descriptiveFont = sponsorFont;
    prepareGradients(MiamiAllAccessHockey::awaySchool.getPrimaryColor(), MiamiAllAccessHockey::homeSchool.getPrimaryColor());
    networkText = "NCHC.tv";
    clockStatus = SHOW_CLOCK;
    descriptiveFont.setCapitalization(QFont::SmallCaps);
    connect(game->getGameClock(), SIGNAL(clockUpdated()), this, SLOT(updateClock()));
    awayLogo = new QPixmap(MiamiAllAccessHockey::awaySchool.getLogo());
    if (awayLogo->height() > LOGO_HEIGHT) {
        *awayLogo = awayLogo->scaledToHeight(LOGO_HEIGHT, Qt::SmoothTransformation);
    }
    if (awayLogo->width() > NAME_WIDTH) {
       *awayLogo =  awayLogo->scaledToWidth(NAME_WIDTH, Qt::SmoothTransformation);
    }
    awayLogoHeightOffset = (LOGO_HEIGHT - awayLogo->height()) / 2;
    awayLogoWidthOffset = (NAME_WIDTH - awayLogo->width()) / 2;
    homeLogo = homeLogo.scaledToHeight(LOGO_HEIGHT, Qt::SmoothTransformation);
    homeLogoWidthOffset = (NAME_WIDTH - homeLogo.width()) / 2;
}

void CommercialGraphic::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                              QWidget* widget) {
    if (show){
        painter->fillRect(0, 0, GRAPHIC_WIDTH, GRAPHIC_HEIGHT, bgGradient);
        painter->fillRect(BORDER_THICKNESS, 10, NAME_WIDTH, RECT_HEIGHT, awayTeamGradient);
        painter->drawPixmap(BORDER_THICKNESS+ awayLogoWidthOffset, 10 + awayLogoHeightOffset, *awayLogo);
        painter->fillRect(BORDER_THICKNESS + NAME_WIDTH + SCORE_WIDTH + CLOCK_WIDTH + SCORE_WIDTH, BORDER_THICKNESS, NAME_WIDTH, RECT_HEIGHT, homeTeamGradient);
        painter->drawPixmap(BORDER_THICKNESS + NAME_WIDTH + SCORE_WIDTH + CLOCK_WIDTH + SCORE_WIDTH + homeLogoWidthOffset, BORDER_THICKNESS, homeLogo);
        painter->fillRect(BORDER_THICKNESS + NAME_WIDTH, BORDER_THICKNESS, 100, RECT_HEIGHT, clockGradient);
        painter->fillRect(BORDER_THICKNESS + NAME_WIDTH + SCORE_WIDTH + CLOCK_WIDTH, BORDER_THICKNESS, 100, RECT_HEIGHT, clockGradient);

        painter->setPen(QColor(255, 255, 255));
        painter->setFont(away->font());
        painter->drawText(BORDER_THICKNESS, LOGO_HEIGHT+BORDER_THICKNESS, NAME_WIDTH, RECT_HEIGHT - LOGO_HEIGHT, Qt::AlignCenter, away->toPlainText());
        painter->setFont(home->font());
        painter->drawText(BORDER_THICKNESS + NAME_WIDTH + SCORE_WIDTH + CLOCK_WIDTH + SCORE_WIDTH, LOGO_HEIGHT+BORDER_THICKNESS, NAME_WIDTH, RECT_HEIGHT - LOGO_HEIGHT, Qt::AlignCenter, home->toPlainText());
        painter->drawPixmap(CLOCK_X + (CLOCK_WIDTH-networkLogo.width()) / 2, 10 + ((90-networkLogo.height()) / 2), networkLogo);
        painter->setFont(descriptiveFont);
        if (clockStatus == FINAL || period == "SHOOTOUT") {
            if (period.endsWith("OT")) {
                painter->drawText(CLOCK_X,120, CLOCK_WIDTH, 50 , Qt::AlignCenter, "FINAL/OT");
            } else{
                painter->drawText(CLOCK_X,120, CLOCK_WIDTH, 50, Qt::AlignCenter, clockStatus == FINAL ? "FINAL" : period);
            }
        }
        else {
            if (clock == "INTERMISSION" && (period == "3RD" || period.endsWith("OT"))) {
                painter->drawText(CLOCK_X,100, CLOCK_WIDTH, 40 , Qt::AlignCenter, "END OF");
                painter->drawText(CLOCK_X,140, CLOCK_WIDTH, 40 , Qt::AlignCenter, (period.contains("OT") ? period : "REGULATION"));
//                painter->drawText(CLOCK_X,160, CLOCK_WIDTH, 40 , Qt::AlignCenter,
//                                  period.contains("OT") ? period : "REGULATION");
            } else {
                painter->drawText(CLOCK_X,100, CLOCK_WIDTH, 40 , Qt::AlignCenter, period);
                painter->drawText(CLOCK_X,140, CLOCK_WIDTH, 40 , Qt::AlignCenter, clock);
//                painter->drawText(CLOCK_X,160, CLOCK_WIDTH, 40 , Qt::AlignCenter, clock);
            }
        }
        if (Globals::onTv) {
            painter->setPen(Globals::tvBrandingTop);
        } else {
            painter->setPen(Globals::nchcBrandingTop);
        }
        painter->setFont(QFont("Arial", 60, QFont::Bold));
        painter->drawText(BORDER_THICKNESS + NAME_WIDTH, BORDER_THICKNESS, SCORE_WIDTH, RECT_HEIGHT, Qt::AlignCenter, awayScore);
        painter->drawText(BORDER_THICKNESS + NAME_WIDTH + CLOCK_WIDTH + SCORE_WIDTH, BORDER_THICKNESS, SCORE_WIDTH, RECT_HEIGHT, Qt::AlignCenter, homeScore);
    }
}

int CommercialGraphic::getWidth()
{
    return GRAPHIC_WIDTH;
}

int CommercialGraphic::getHeight()
{
    return GRAPHIC_HEIGHT;
}

void CommercialGraphic::prepareAndShow()
{
    awayScore = QString::number(hockeyGame->getAwayScore());
    homeScore = QString::number(hockeyGame->getHomeScore());
    emit addNoTransparencyZone(QRect(x() + 10, y() + 10, NAME_WIDTH, RECT_HEIGHT));
    if (Globals::onTv) {
        emit addNoTransparencyZone(QRect(x() + CLOCK_X + (CLOCK_WIDTH-networkLogo.width()) / 2, y() + 10, networkLogo.width(), networkLogo.height()));
    }
    switch (hockeyGame->getPeriod()) {
    case 0:
        inGame = false;
        period = "STARTS IN";
        break;
    case 1:
        inGame = true;
        period = "1ST";
        break;
    case 2:
        period = "2ND";
        break;
    case 3:
        period = "3RD";
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
            scene()->update(x() + CLOCK_X, y(), CLOCK_WIDTH, GRAPHIC_HEIGHT);
        }
        else if (clockStatus == INTERMISSION) {
            clock = "INTERMISSION";
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
        scene()->update(x() + CLOCK_X, y(), CLOCK_WIDTH, GRAPHIC_HEIGHT);
}

void CommercialGraphic::intermissionTime()
{
    clockStatus = INTERMISSION;
    updateClock();
    if (show)
        scene()->update(x() + CLOCK_X, y(), CLOCK_WIDTH, GRAPHIC_HEIGHT);
}

void CommercialGraphic::finalTime()
{
    clockStatus = FINAL;
    updateClock();
    if (show)
        scene()->update(x() + CLOCK_X, y(), CLOCK_WIDTH, GRAPHIC_HEIGHT);
}

void CommercialGraphic::hide()
{
    if (show) {
        show = false;
        emit removeNoTransparencyZone(QRect(x() + 10, y() + 10, NAME_WIDTH, RECT_HEIGHT));
        if (Globals::onTv) {
            emit removeNoTransparencyZone(QRect(x() + CLOCK_X + (CLOCK_WIDTH-networkLogo.width()) / 2, y() + 10, networkLogo.width(), networkLogo.height()));
        }
        scene()->update();
    }
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
    awayTeamGradient.setStart(0, 10);
    awayTeamGradient.setFinalStop(0, RECT_HEIGHT-10);
    homeTeamGradient.setStart(0,10);
    homeTeamGradient.setFinalStop(0, RECT_HEIGHT-10);
    int red, green, blue;
    red = -1*homeColor.red() *GRADIENT_LEVEL + homeColor.red();
    green = -1*homeColor.green() *GRADIENT_LEVEL + homeColor.green();
    blue = -1*homeColor.blue() *GRADIENT_LEVEL + homeColor.blue();

    QColor end(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    homeTeamGradient.setColorAt(0, homeColor);
    homeTeamGradient.setColorAt(1, end);

    red = -1*awayColor.red() *GRADIENT_LEVEL + awayColor.red();
    green = -1*awayColor.green() *GRADIENT_LEVEL + awayColor.green();
    blue = -1*awayColor.blue() *GRADIENT_LEVEL + awayColor.blue();
    QColor end2(red, green, blue);
    if (end2 == QColor(0,0,0))
        end2 = QColor(1,1,1);
    awayTeamGradient.setColorAt(0, awayColor);
    awayTeamGradient.setColorAt(1, end2);


    clockGradient.setStart(0, 10);
    clockGradient.setFinalStop(0, RECT_HEIGHT + 10);
    QColor blueWhite(196, 213, 242);
    red = -1*blueWhite.red() *GRADIENT_LEVEL + blueWhite.red();
    green = -1*blueWhite.green() *GRADIENT_LEVEL + blueWhite.green();
    blue = -1*blueWhite.blue() *GRADIENT_LEVEL + blueWhite.blue();

    QColor end3(red, green, blue);
    if (end3 == QColor(0,0,0))
        end3 = QColor(1,1,1);
    clockGradient.setColorAt(1, end3);
    clockGradient.setColorAt(0, blueWhite);

    bgGradient.setStart(0,0);
    bgGradient.setFinalStop(0, GRAPHIC_HEIGHT);

    if (Globals::onTv) {
        bgGradient.setColorAt(0, Globals::tvBrandingTop);
        bgGradient.setColorAt(1, Globals::tvBrandingBottom);
    } else {
        bgGradient.setColorAt(0, Globals::nchcBrandingTop);
        bgGradient.setColorAt(1, Globals::nchcBrandingBottom);
    }
    //bgGradient.setColorAt(.5, QColor(50,50,50));
}

void CommercialGraphic::changeUseClock(bool uc)
{
    useClock = uc;
    if (show) {
        updateClock();
    }
}

void CommercialGraphic::toggleAwayLogoBg(bool on)
{
    altAwayLogoBg = on;
    if (show) {
        scene()->update();
    }
}
