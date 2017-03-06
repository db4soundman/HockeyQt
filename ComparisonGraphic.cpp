#include "ComparisonGraphic.h"
#include <QGraphicsScene>
#include <QFontMetrics>
#include <QStringRef>
#include <QGraphicsScene>
#include <QRect>
#include <algorithm>


#define NAME_GRADIENT_LEVEL .4
#define STAT_GRADIENT_LEVEL .4
#define NAME_WIDTH 460
#define BOX_HEIGHT 38

ComparisonGraphic::ComparisonGraphic(QColor awayColor, QColor homeColor, QPixmap pawayLogo):
    awayTeamMain(awayColor), homeTeamMain(homeColor), statFont("Arial", 22, QFont::Bold),
    nameFont("Arial", 28, QFont::Bold), labelFont("Arial", 18, QFont::Bold)
{
    show = false;
    statHeader = "";
    setRect(0,0,800,BOX_HEIGHT*3);
    statFontPointSize = statFont.pointSize();

    bgGradient.setStart(0, BOX_HEIGHT);
    bgGradient.setFinalStop(0, BOX_HEIGHT * 3);
    statHeaderGradient.setStart(0, 0);
    statHeaderGradient.setFinalStop(0, BOX_HEIGHT);
    homeStatGradient.setStart(0, BOX_HEIGHT*2);
    homeStatGradient.setFinalStop(0, BOX_HEIGHT * 3);
    awayStatGradient.setStart(0, BOX_HEIGHT);
    awayStatGradient.setFinalStop(0, BOX_HEIGHT*2);
    homeLogo = new QPixmap(":/images/M.png");
    awayLogo = new QPixmap(pawayLogo);

    *homeLogo = homeLogo->scaledToHeight(BOX_HEIGHT, Qt::SmoothTransformation);
    *awayLogo = awayLogo->scaledToHeight(BOX_HEIGHT, Qt::SmoothTransformation);
    awayLogoOffset = std::max((50 - awayLogo->width()) / 2, 0);
    prepareColors();
}

void ComparisonGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (show) {
        for (int i = x(); i < x() + this->rect().width(); i++) {
            for (int j = y(); j < y() + this->rect().height(); j++) {
                canvas->setPixelColor(i,j,QColor(0,0,0,0));
            }
        }
        QPainter p(canvas);
        p.translate(x(), y());
        draw(&p);
        draw(painter);
    }
}

void ComparisonGraphic::hideComparison()
{
    if (show) {
        show = false;
        for (int i = x(); i < x() + this->rect().width(); i++) {
            for (int j = y(); j < y() + this->rect().height(); j++) {
                canvas->setPixelColor(i,j,QColor(0,0,0,0));
            }
        }
        // TODO update this
        scene()->update(this->x(), this->y(), rect().width(), rect().height());
    }
}

void ComparisonGraphic::showComparison()
{

    show = true;
    scene()->update(this->x(), this->y(), rect().width(), rect().height());

}

void ComparisonGraphic::prepareComp( QString awayLabel,QString homeLabel, QList<QString> stats, QString pstatHeader)
{
    statFont.setPointSize(statFontPointSize);
    statHeader = pstatHeader;
    this->awayLabel = awayLabel;
    this->homeLabel = homeLabel;
    statistics=stats;
    prepareFontSize();
    showComparison();
}

void ComparisonGraphic::setCanvas(QImage *value)
{
    canvas = value;
}

void ComparisonGraphic::prepareColors()
{
    int red, green, blue;

    bgGradient.setColorAt(0, QColor(41, 70, 91));
    bgGradient.setColorAt(1, QColor(23, 41, 53));


    red = -1*homeTeamMain.red() *STAT_GRADIENT_LEVEL + homeTeamMain.red();
    green = -1*homeTeamMain.green() *STAT_GRADIENT_LEVEL + homeTeamMain.green();
    blue = -1*homeTeamMain.blue() *STAT_GRADIENT_LEVEL + homeTeamMain.blue();
    QColor end(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    homeStatGradient.setColorAt(0, homeTeamMain);
    //homeStatGradient.setColorAt(.6, homeTeamMain);
    homeStatGradient.setColorAt(1, end);
    //homeStatGradient.setColorAt(0, end);

// -------------------------------------Away Team--------------------------------

    red = -1*awayTeamMain.red() *STAT_GRADIENT_LEVEL + awayTeamMain.red();
    green = -1*awayTeamMain.green() *STAT_GRADIENT_LEVEL + awayTeamMain.green();
    blue = -1*awayTeamMain.blue() *STAT_GRADIENT_LEVEL + awayTeamMain.blue();
    end.setRgb(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    awayStatGradient.setColorAt(0, awayTeamMain);
    awayStatGradient.setColorAt(1, end);

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

void ComparisonGraphic::draw(QPainter *painter)
{
    if (!statHeader.isEmpty()) {
        painter->setFont(statFont);
        QFontMetrics fontSize(statFont);
        painter->fillRect(0, BOX_HEIGHT-24, fontSize.width(statHeader) + 10, 24, statHeaderGradient );
        painter->setPen(QColor(1,1,1));
        painter->drawText(0, BOX_HEIGHT-24,fontSize.width(statHeader) + 10, 24, Qt::AlignCenter, statHeader);
    }
   painter->fillRect(0, BOX_HEIGHT, statistics.size() > 2 ? 800 : 600, BOX_HEIGHT * 2, bgGradient);
   painter->fillRect(55, BOX_HEIGHT, statistics.size() > 2 ? 740 : 540, BOX_HEIGHT, awayStatGradient);
   painter->fillRect(55, BOX_HEIGHT * 2, statistics.size() > 2 ? 740 : 540, BOX_HEIGHT, homeStatGradient);
   painter->drawPixmap(1 + awayLogoOffset, BOX_HEIGHT,*awayLogo);
   painter->drawPixmap(1, BOX_HEIGHT*2,*homeLogo);
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


