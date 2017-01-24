#include "LowerThird.h"
#include <QFontMetrics>
#include <QStringRef>
#include <QGraphicsScene>
#include <QRect>
#include "GraphicChooser.txt"


#define NAME_GRADIENT_LEVEL .1
#define STAT_GRADIENT_LEVEL .1
#define NAME_WIDTH 460
#define BOX_HEIGHT 38
LowerThird::LowerThird(QColor awayColor, QColor homeColor, int screenWidth, QPixmap pawayLogo, QGraphicsItem* parent) :
    name(""), number("number"), statFont("Arial", 22, QFont::Bold), nameFont("Arial", 28, QFont::Bold), labelFont("Arial", 18, QFont::Bold),
    awayTeamMain(awayColor), homeTeamMain(homeColor) {
#ifdef Q_OS_OSX
    statFont.setPointSize(36);
    nameFont.setPointSize(36);
    #endif
    fontPointSize = nameFont.pointSize();
    //setPixmap(QPixmap(":/images/LowerThird.png"));
    setRect(0,0,1200, BOX_HEIGHT*3);
    statFontPointSize = statFont.pointSize();
    gradient.setStart(0, 0);
    gradient.setFinalStop(0, BOX_HEIGHT);
    homeNameGradient.setStart(0, 0);
    homeNameGradient.setFinalStop(0, BOX_HEIGHT);
    awayNameGradient.setStart(0, 0);
    awayNameGradient.setFinalStop(0, BOX_HEIGHT);
    statGradient.setStart(0, BOX_HEIGHT);
    statGradient.setFinalStop(0, BOX_HEIGHT * 2);
    homeStatGradient.setStart(0, BOX_HEIGHT);
    homeStatGradient.setFinalStop(0, BOX_HEIGHT * 2);
    awayStatGradient.setStart(0, 0);
    awayStatGradient.setFinalStop(0, BOX_HEIGHT);
    prepareColors();
    statistics.append("");
    statNames.append("");
    this->centerPoint = screenWidth / 2;
    show = false;
    homeLogo = new QPixmap(":/images/M.png");
    awayLogo = new QPixmap(pawayLogo);

    *homeLogo = homeLogo->scaledToHeight(BOX_HEIGHT, Qt::SmoothTransformation);
    *awayLogo = awayLogo->scaledToHeight(BOX_HEIGHT, Qt::SmoothTransformation);
}

void
LowerThird::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (show) {
        //painter->drawPixmap(0, 0, this->pixmap());
        painter->fillRect(0, 0, 600, BOX_HEIGHT, gradient);
        painter->fillRect(0, BOX_HEIGHT, 1000, BOX_HEIGHT, statGradient);


        painter->setFont(nameFont);
        painter->setPen(QColor(255,255,255));
        painter->drawText(60, 0, NAME_WIDTH + 20, BOX_HEIGHT, Qt::AlignCenter, name);
        painter->drawText(0, 0, 60, BOX_HEIGHT, Qt::AlignCenter, number);
        painter->drawText(530, 0, 60, BOX_HEIGHT, Qt::AlignCenter, year);


        int rectWidth = 1000/statistics.size();

        painter->setPen(QColor(255, 255, 255));
        // Stat numbers
        for (int i = 0; i< statistics.size(); i++) {
            painter->setFont(statFont);
            painter->drawText(rectWidth * i, BOX_HEIGHT, rectWidth, BOX_HEIGHT, Qt::AlignCenter, statistics.at(i)+ " " + (statNames.size() > i ? statNames.at(i) : " "));
            //painter->setFont(labelFont);
           // painter->drawText(rectWidth * i + 100, BOX_HEIGHT, rectWidth, BOX_HEIGHT, Qt::AlignRight | Qt::AlignBottom, statNames.size() > i ? statNames.at(i) : " ");
        }
        //painter->setPen(QColor(255, 255, 255));


    }
    /**else if (showPp) {
        //int availableWidth = centerPoint - 772;
        //painter->drawPixmap(availableWidth / 2 - this->x() + 372, 0, 400, 120, this->pixmap());
        painter->fillRect(0, 0, statistics.size() > 2 ? 800 : 600, BOX_HEIGHT, awayNameGradient);
        painter->fillRect(0, BOX_HEIGHT, statistics.size() > 2 ? 800 : 600, BOX_HEIGHT, homeStatGradient);
        painter->drawPixmap(1, 0,*awayLogo);
        painter->drawPixmap(1, BOX_HEIGHT,*homeLogo);
        painter->setFont(nameFont);
        painter->setPen(QColor(255, 255, 255));
        painter->drawText(100, 0, 400, BOX_HEIGHT, Qt::AlignVCenter, awayLabel);
        painter->drawText(400, 0, 200, BOX_HEIGHT, Qt::AlignVCenter, statistics.at(0));
        painter->drawText(100, BOX_HEIGHT, 400, BOX_HEIGHT, Qt::AlignVCenter, homeLabel);
        painter->drawText(400, BOX_HEIGHT, 200, BOX_HEIGHT, Qt::AlignVCenter, statistics.at(1));
        if (statistics.size() > 2) {
            painter->drawText(600, 0, 200 ,BOX_HEIGHT, Qt::AlignVCenter, statistics.at(2));
            painter->drawText(600, BOX_HEIGHT, 200 ,BOX_HEIGHT, Qt::AlignVCenter, statistics.at(3));
        }
    }*/
}

void
LowerThird::prepareForDisplay(QString name, QString number, QString year,
                              QList<QString> statLabels,
                              QList<QString> statValues, bool homeTeam) {
    this->name = name;
//    if (name.contains(" ")) {
//        firstName = name.left(name.indexOf(" "));
//        QStringRef substr(&name, name.indexOf(" ") + 1, name.length() - (name.indexOf(" ")+1));
//        lastName = substr.toString();
//    }
//    else {
//        firstName = name;
//        lastName = "";
//    }
    this->year = year;
    this->number = number;
    statNames = statLabels;
    statistics = statValues;
    gradient = homeTeam ? homeNameGradient : awayNameGradient;
   // statGradient = homeTeam ? homeStatGradient : awayStatGradient;
    prepareFontSize();
    // To ensure font size is returned to normal in the event that
    // a custom text LT was used.
    statFont.setPointSize(statFontPointSize);
    showLt();
}

void LowerThird::prepareForCustomLt(QString name, QString number, QString year,
                                    QList<QString> statLabels,
                                    QList<QString> statValues, bool homeTeam)
{
    statFont.setPointSize(statFontPointSize);
    this->name = name;
    if (name.contains(" ")) {
        firstName = name.left(name.indexOf(" "));
        QStringRef substr(&name, name.indexOf(" ") + 1, name.length() - (name.indexOf(" ")+1));
        lastName = substr.toString();
    }
    else {
        firstName = name;
        lastName = "";
    }
    this->year = year;
    this->number = number;
    statNames = statLabels;
    statistics = statValues;
    gradient = homeTeam ? homeNameGradient : awayNameGradient;
    //statGradient = homeTeam ? homeStatGradient : awayStatGradient;
    // Resize the font to be two lines ONLY if necessary...
    QFontMetrics fontSize(statFont);
    if (fontSize.width(statistics[0]) > this->rect().width() - 100)
        adjustFont();
    showLt();
}
void LowerThird::prepareColors() {
    int red, green, blue;
    red = -1*homeTeamMain.red() *NAME_GRADIENT_LEVEL + homeTeamMain.red();
    green = -1*homeTeamMain.green() *NAME_GRADIENT_LEVEL + homeTeamMain.green();
    blue = -1*homeTeamMain.blue() *NAME_GRADIENT_LEVEL + homeTeamMain.blue();

    QColor end(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    homeNameGradient.setColorAt(.4, homeTeamMain);
    homeNameGradient.setColorAt(.6, homeTeamMain);
    homeNameGradient.setColorAt(1, end);
    homeNameGradient.setColorAt(0, end);

    red = -1*homeTeamMain.red() *STAT_GRADIENT_LEVEL + homeTeamMain.red();
    green = -1*homeTeamMain.green() *STAT_GRADIENT_LEVEL + homeTeamMain.green();
    blue = -1*homeTeamMain.blue() *STAT_GRADIENT_LEVEL + homeTeamMain.blue();
    end.setRgb(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    homeStatGradient.setColorAt(.4, homeTeamMain);
    homeStatGradient.setColorAt(.6, homeTeamMain);
    homeStatGradient.setColorAt(1, end);
    homeStatGradient.setColorAt(0, end);

// -------------------------------------Away Team--------------------------------

    red = -1*awayTeamMain.red() *NAME_GRADIENT_LEVEL + awayTeamMain.red();
    green = -1*awayTeamMain.green() *NAME_GRADIENT_LEVEL + awayTeamMain.green();
    blue = -1*awayTeamMain.blue() *NAME_GRADIENT_LEVEL + awayTeamMain.blue();
    end.setRgb(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    awayNameGradient.setColorAt(0.45, awayTeamMain);
    awayNameGradient.setColorAt(0.55, awayTeamMain);
    awayNameGradient.setColorAt(1, end);
    awayNameGradient.setColorAt(0, end);

    red = -1*awayTeamMain.red() *STAT_GRADIENT_LEVEL + awayTeamMain.red();
    green = -1*awayTeamMain.green() *STAT_GRADIENT_LEVEL + awayTeamMain.green();
    blue = -1*awayTeamMain.blue() *STAT_GRADIENT_LEVEL + awayTeamMain.blue();
    end.setRgb(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    awayStatGradient.setColorAt(.5, awayTeamMain);
    awayStatGradient.setColorAt(1, end);
    awayStatGradient.setColorAt(0, end);


    stats = QColor(20,20,20);
    red = -1*stats.red() *STAT_GRADIENT_LEVEL + stats.red();
    green = -1*stats.green() *STAT_GRADIENT_LEVEL + stats.green();
    blue = -1*stats.blue() *STAT_GRADIENT_LEVEL + stats.blue();
    end.setRgb(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
   // statGradient.setColorAt(.5, stats);
    statGradient.setColorAt(1, QColor(23, 41, 53));
    statGradient.setColorAt(0, QColor(41, 70, 91));
}

void
LowerThird::prepareFontSize() {
    int subtraction = 1;
    QFontMetrics fontSize(nameFont);
    while (fontSize.width(name) > NAME_WIDTH) {
        QFont tempFont("Arial", fontPointSize - subtraction, QFont::Bold);
        //nameFont.setPointSize(fontPointSize - subtraction);
        subtraction++;
        nameFont = tempFont;
        QFontMetrics temp(nameFont);
        fontSize = temp;
    }
}

void LowerThird::adjustFont()
{
    statFont.setPointSize(22);
#ifdef Q_OS_OSX
    statFont.setPointSize(28);
#endif
    int subtraction = 1;
    QFontMetrics fontSize(statFont);
    while (fontSize.width(statistics[0]) > 1000 - 10) {
        QFont tempFont("Arial", statFont.pointSize() - subtraction, QFont::Bold);
        subtraction++;
        statFont = tempFont;
        QFontMetrics temp(statFont);
        fontSize = temp;
    }
}

void LowerThird::prepareComp(QString awayName, QString awayLabel,
                                   QString homeName, QString homeLabel, QList<QString> stats) {
     statFont.setPointSize(statFontPointSize);
     this->awayName = awayName;
     this->awayLabel = awayLabel;
     this->homeName = homeName;
     this->homeLabel = homeLabel;
     statistics=stats;
     prepareFontSize();
     showPpComp();

 }


void
LowerThird::hideLt() {
    if (show) {
        show = false;
        scene()->update();
    }
}

void
LowerThird::showLt() {
    show = true;
    scene()->update();
}

void LowerThird::showPpComp()
{
    show = false;
    scene()->update();
}
