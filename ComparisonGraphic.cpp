#include "ComparisonGraphic.h"
#include <QGraphicsScene>
#include <QFontMetrics>
#include <QStringRef>
#include <QGraphicsScene>
#include <algorithm>
#include "MiamiAllAccessHockey.h"
#include "globals.h"

#define NAME_GRADIENT_LEVEL .4
#define STAT_GRADIENT_LEVEL .4
#define NAME_WIDTH 460
#define BOX_HEIGHT 38

ComparisonGraphic::ComparisonGraphic(bool preview):
    awayTeamMain(MiamiAllAccessHockey::awaySchool.getPrimaryColor()),
    homeTeamMain(MiamiAllAccessHockey::homeSchool.getPrimaryColor()),
    statFont("Arial", 22, QFont::Bold), nameFont("Arial", 28, QFont::Bold),
    labelFont("Arial", 18, QFont::Bold)
{
    this->preview = preview;
    show = false;
    statHeader = "";
    setRect(0,0,800,BOX_HEIGHT*3);
    statFontPointSize = statFont.pointSize();

    bgGradient.setStart(0, BOX_HEIGHT);
    bgGradient.setFinalStop(0, BOX_HEIGHT * 3);
    statHeaderGradient.setStart(0, 0);
    statHeaderGradient.setFinalStop(0, BOX_HEIGHT);
    bottomGradient.setStart(0, BOX_HEIGHT*2);
    bottomGradient.setFinalStop(0, BOX_HEIGHT * 3);
    topGradient.setStart(0, BOX_HEIGHT);
    topGradient.setFinalStop(0, BOX_HEIGHT*2);
    homeLogo = new QPixmap(MiamiAllAccessHockey::homeSchool.getLogo());
    awayLogo = new QPixmap(MiamiAllAccessHockey::awaySchool.getLogo());

    *homeLogo = homeLogo->scaledToHeight(BOX_HEIGHT, Qt::SmoothTransformation);
    *awayLogo = awayLogo->scaledToHeight(BOX_HEIGHT, Qt::SmoothTransformation);

    if (awayLogo->width() > 50) {
        *awayLogo = awayLogo->scaledToWidth(50, Qt::SmoothTransformation);
    }

    awayLogoXOffset = std::max((50 - awayLogo->width()) / 2, 0);
    awayLogoYOffset = std::max((BOX_HEIGHT - awayLogo->height()) / 2, 0);
    topOffset = true;
    botOffset = false;
    prepareColors();
}

void ComparisonGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (show) {
        if (!statHeader.trimmed().isEmpty()) {
            painter->setFont(statFont);
            QFontMetrics fontSize(statFont);
            painter->fillRect(0, BOX_HEIGHT-24, fontSize.width(statHeader) + 10, 24, statHeaderGradient );
            painter->setPen(QColor(1,1,1));
            painter->drawText(0, BOX_HEIGHT-24,fontSize.width(statHeader) + 10, 24, Qt::AlignCenter, statHeader);
        }
       painter->fillRect(0, BOX_HEIGHT, statistics.size() > 2 ? 800 : 600, BOX_HEIGHT * 2, bgGradient);
       painter->fillRect(5, BOX_HEIGHT, statistics.size() > 2 ? 790 : 590, BOX_HEIGHT, topGradient);
       painter->fillRect(5, BOX_HEIGHT * 2, statistics.size() > 2 ? 790 : 590, BOX_HEIGHT, bottomGradient);
       painter->drawPixmap(5 + (topOffset ?  awayLogoXOffset : 0), BOX_HEIGHT + (topOffset ? awayLogoYOffset : 0),topOffset ? *awayLogo:*homeLogo);
       painter->drawPixmap(5 + (botOffset ? awayLogoXOffset : 0), BOX_HEIGHT*2 +( botOffset ? awayLogoYOffset : 0),botOffset ? *awayLogo:*homeLogo);
       painter->setFont(nameFont);
       painter->setPen(QColor(255, 255, 255));
       painter->drawText(100, BOX_HEIGHT, 400, BOX_HEIGHT, Qt::AlignVCenter, awayLabel);
       painter->drawText(400, BOX_HEIGHT, 200, BOX_HEIGHT, Qt::AlignVCenter, statistics.at(0));
       painter->drawText(100, BOX_HEIGHT*2, 400, BOX_HEIGHT, Qt::AlignVCenter, homeLabel);
       painter->drawText(400, BOX_HEIGHT*2, 200, BOX_HEIGHT, Qt::AlignVCenter, statistics.at(1));
       if (statistics.size() > 2) {
           painter->drawText(600, BOX_HEIGHT, 200 ,BOX_HEIGHT, Qt::AlignVCenter, statistics.at(2));
           painter->drawText(600, BOX_HEIGHT*2, 200 ,BOX_HEIGHT, Qt::AlignVCenter, statistics.at(3));
       }
    }
}

void ComparisonGraphic::paintPreview(QPainter *painter)
{
    if (!statHeader.trimmed().isEmpty()) {
        painter->setFont(statFont);
        QFontMetrics fontSize(statFont);
        painter->fillRect(0, BOX_HEIGHT-24, fontSize.width(statHeader) + 10, 24, statHeaderGradient );
        painter->setPen(QColor(1,1,1));
        painter->drawText(0, BOX_HEIGHT-24,fontSize.width(statHeader) + 10, 24, Qt::AlignCenter, statHeader);
    }
   painter->fillRect(0, BOX_HEIGHT, statistics.size() > 2 ? 800 : 600, BOX_HEIGHT * 2, bgGradient);
   painter->fillRect(5, BOX_HEIGHT, statistics.size() > 2 ? 790 : 590, BOX_HEIGHT, topGradient);
   painter->fillRect(5, BOX_HEIGHT * 2, statistics.size() > 2 ? 790 : 590, BOX_HEIGHT, bottomGradient);
   painter->drawPixmap(5 + (topOffset ?  awayLogoXOffset : 0), BOX_HEIGHT + (topOffset ? awayLogoYOffset : 0),topOffset ? *awayLogo:*homeLogo);
   painter->drawPixmap(5 + (botOffset ? awayLogoXOffset : 0), BOX_HEIGHT*2 +( botOffset ? awayLogoYOffset : 0),botOffset ? *awayLogo:*homeLogo);
   painter->setFont(nameFont);
   painter->setPen(QColor(255, 255, 255));
   painter->drawText(100, BOX_HEIGHT, 400, BOX_HEIGHT, Qt::AlignVCenter, awayLabel);
   painter->drawText(400, BOX_HEIGHT, 200, BOX_HEIGHT, Qt::AlignVCenter, statistics.at(0));
   painter->drawText(100, BOX_HEIGHT*2, 400, BOX_HEIGHT, Qt::AlignVCenter, homeLabel);
   painter->drawText(400, BOX_HEIGHT*2, 200, BOX_HEIGHT, Qt::AlignVCenter, statistics.at(1));
   if (statistics.size() > 2) {
       painter->drawText(600, BOX_HEIGHT, 200 ,BOX_HEIGHT, Qt::AlignVCenter, statistics.at(2));
       painter->drawText(600, BOX_HEIGHT*2, 200 ,BOX_HEIGHT, Qt::AlignVCenter, statistics.at(3));
   }
}

int ComparisonGraphic::getWidth()
{
    return rect().width();
}

int ComparisonGraphic::getHeight()
{
    return rect().height();
}

void ComparisonGraphic::hideComparison()
{
    if (show) {
        show = false;
        if (!statHeader.trimmed().isEmpty()) {
            QFontMetrics fontSize(statFont);
            emit removeNoTransparencyZone(QRect(x(), y() + BOX_HEIGHT-24, fontSize.width(statHeader) + 10, 24));
        }
        emit removeNoTransparencyZone(QRect(x(), y() + BOX_HEIGHT, statistics.size() > 2 ? 800 : 600, BOX_HEIGHT * 2));
        scene()->update(this->x(), this->y(), rect().width(), rect().height());
    }
}

void ComparisonGraphic::showComparison()
{

    show = true;
    if (!statHeader.trimmed().isEmpty()) {
        QFontMetrics fontSize(statFont);
        emit addNoTransparencyZone(QRect(x(), y() + BOX_HEIGHT-24, fontSize.width(statHeader) + 10, 24));
    }
    emit addNoTransparencyZone(QRect(x(), y() + BOX_HEIGHT, statistics.size() > 2 ? 800 : 600, BOX_HEIGHT * 2));
    scene()->update(this->x(), this->y(), rect().width(), rect().height());

}

void ComparisonGraphic::prepareComp(QString topLabel, QString botLabel, QList<QString> stats, QString pStatHeader, int compStyle)
{
    if(!preview && show) {
        if (!statHeader.trimmed().isEmpty()) {
            QFontMetrics fontSize(statFont);
            emit removeNoTransparencyZone(QRect(x(), y() + BOX_HEIGHT-24, fontSize.width(statHeader) + 10, 24));
        }
        emit removeNoTransparencyZone(QRect(x(), y() + BOX_HEIGHT, statistics.size() > 2 ? 800 : 600, BOX_HEIGHT * 2));
    }

    statFont.setPointSize(statFontPointSize);
    statHeader = pStatHeader;
    this->awayLabel = topLabel;
    this->homeLabel = botLabel;
    statistics=stats;
    prepareFontSize();

    topOffset = compStyle != 2;
    botOffset = compStyle == 1;

    switch(compStyle) {
    case 0:
        topGradient.setColorAt(0, awayTeamMain);
        topGradient.setColorAt(1, awayGradientEnd);
        bottomGradient.setColorAt(0, homeTeamMain);
        bottomGradient.setColorAt(1, homeGradientEnd);
//        topLogo = awayLogo;
//        bottomLogo = homeLogo;
        break;
    case 1:
        topGradient.setColorAt(0, awayTeamMain);
        topGradient.setColorAt(1, awayGradientEnd);
        bottomGradient.setColorAt(0, awayTeamMain);
        bottomGradient.setColorAt(1, awayGradientEnd);
//        topLogo = awayLogo;
//        bottomLogo = awayLogo;
        break;
    case 2:
        topGradient.setColorAt(0, homeTeamMain);
        topGradient.setColorAt(1, homeGradientEnd);
        bottomGradient.setColorAt(0, homeTeamMain);
        bottomGradient.setColorAt(1, homeGradientEnd);
//        topLogo = homeLogo;
//        bottomLogo = homeLogo;
        break;
    }


    if (!preview) showComparison();
}

void ComparisonGraphic::prepareStandardComp( QString awayLabel,QString homeLabel, QList<QString> stats, QString pstatHeader)
{
    prepareComp(awayLabel, homeLabel, stats, pstatHeader, 0);
}


void ComparisonGraphic::prepareColors()
{
    int red, green, blue;

    if (Globals::onTv) {
        bgGradient.setColorAt(0, Globals::tvBrandingTop);
        bgGradient.setColorAt(1, Globals::tvBrandingBottom);
    } else {
        bgGradient.setColorAt(0, Globals::nchcBrandingTop);
        bgGradient.setColorAt(1, Globals::nchcBrandingBottom);
    }

    red = -1*homeTeamMain.red() *STAT_GRADIENT_LEVEL + homeTeamMain.red();
    green = -1*homeTeamMain.green() *STAT_GRADIENT_LEVEL + homeTeamMain.green();
    blue = -1*homeTeamMain.blue() *STAT_GRADIENT_LEVEL + homeTeamMain.blue();
    QColor end(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    homeGradientEnd = end;


// -------------------------------------Away Team--------------------------------

    red = -1*awayTeamMain.red() *STAT_GRADIENT_LEVEL + awayTeamMain.red();
    green = -1*awayTeamMain.green() *STAT_GRADIENT_LEVEL + awayTeamMain.green();
    blue = -1*awayTeamMain.blue() *STAT_GRADIENT_LEVEL + awayTeamMain.blue();
    end.setRgb(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
   awayGradientEnd = end;

    QColor blueWhite(196, 213, 242);
    red = -1*blueWhite.red() *STAT_GRADIENT_LEVEL + blueWhite.red();
    green = -1*blueWhite.green() *STAT_GRADIENT_LEVEL + blueWhite.green();
    blue = -1*blueWhite.blue() *STAT_GRADIENT_LEVEL + blueWhite.blue();

    QColor end3(red, green, blue);
    if (end3 == QColor(0,0,0))
        end3 = QColor(1,1,1);
    statHeaderGradient.setColorAt(1, end3);
    statHeaderGradient.setColorAt(0, blueWhite);
}

void ComparisonGraphic::prepareFontSize()
{
//    int subtraction = 1;
//    QFontMetrics fontSize(nameFont);
//    while (fontSize.width(name) > NAME_WIDTH) {
//        QFont tempFont("Arial", fontPointSize - subtraction, QFont::Bold);
//        subtraction++;
//        nameFont = tempFont;
//        QFontMetrics temp(nameFont);
//        fontSize = temp;
//    }
}


