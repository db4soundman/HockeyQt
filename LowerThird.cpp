#include "LowerThird.h"
#include <QFontMetrics>
#include <QStringRef>
#include <QGraphicsScene>
#include <QRect>
#include "GraphicChooser.txt"


#define NAME_GRADIENT_LEVEL .3
#define STAT_GRADIENT_LEVEL .3
#define NAME_WIDTH 300
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
    setRect(0,0,1000, BOX_HEIGHT*3);
    statFontPointSize = statFont.pointSize();
    gradient.setStart(0, 0);
    gradient.setFinalStop(0, BOX_HEIGHT*3);
    homeNameGradient.setStart(0, 0);
    homeNameGradient.setFinalStop(0, BOX_HEIGHT*2);
    awayNameGradient.setStart(0, 0);
    awayNameGradient.setFinalStop(0, BOX_HEIGHT*2);
    statGradient.setStart(0, 0);
    statGradient.setFinalStop(0, BOX_HEIGHT * 3);
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
        //painter->fillRect(0, 0, 100, BOX_HEIGHT, gradient);
        painter->fillRect(0, 0, 1000, BOX_HEIGHT*2, statGradient);


        painter->setFont(nameFont);
        painter->setPen(QColor(255,255,255));
        painter->fillRect(0,0,NAME_WIDTH, BOX_HEIGHT*2, gradient);
        painter->drawText(60, 0, NAME_WIDTH, BOX_HEIGHT, Qt::AlignVCenter, firstName);
        painter->drawText(60, BOX_HEIGHT, NAME_WIDTH, BOX_HEIGHT, Qt::AlignVCenter, lastName);
        painter->setFont(labelFont);
        painter->drawText(0, 0, 60, BOX_HEIGHT, Qt::AlignCenter, number);
        painter->drawText(0, BOX_HEIGHT, 60, BOX_HEIGHT, Qt::AlignCenter, year);


        int rectWidth = (1000 - NAME_WIDTH)/statistics.size();

        painter->setPen(QColor(255, 255, 255));
        // Stat numbers
        for (int i = 0; i< statistics.size(); i++) {
            painter->setFont(statFont);
            painter->drawText(rectWidth * i + NAME_WIDTH, BOX_HEIGHT, rectWidth, BOX_HEIGHT, Qt::AlignHCenter | Qt::AlignBottom, statistics.at(i));
            painter->setFont(labelFont);
            painter->drawText(rectWidth * i + NAME_WIDTH, 0, rectWidth, BOX_HEIGHT, Qt::AlignHCenter | Qt::AlignTop, statNames.size() > i ? statNames.at(i) : " ");
        }
        //painter->setPen(QColor(255, 255, 255));


    }
}

void
LowerThird::prepareForDisplay(QString name, QString number, QString year,
                              QList<QString> statLabels,
                              QList<QString> statValues, bool homeTeam) {
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
    if (fontSize.width(statistics[0]) > this->rect().width() - NAME_WIDTH)
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
    //homeNameGradient.setColorAt(.4, homeTeamMain);
    homeNameGradient.setColorAt(0, homeTeamMain);
    homeNameGradient.setColorAt(1, end);
    //homeNameGradient.setColorAt(0, end);

    red = -1*homeTeamMain.red() *STAT_GRADIENT_LEVEL + homeTeamMain.red();
    green = -1*homeTeamMain.green() *STAT_GRADIENT_LEVEL + homeTeamMain.green();
    blue = -1*homeTeamMain.blue() *STAT_GRADIENT_LEVEL + homeTeamMain.blue();
    end.setRgb(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
  //  homeStatGradient.setColorAt(.4, homeTeamMain);
    homeStatGradient.setColorAt(0, homeTeamMain);
    homeStatGradient.setColorAt(1, end);
   // homeStatGradient.setColorAt(0, end);

// -------------------------------------Away Team--------------------------------

    red = -1*awayTeamMain.red() *NAME_GRADIENT_LEVEL + awayTeamMain.red();
    green = -1*awayTeamMain.green() *NAME_GRADIENT_LEVEL + awayTeamMain.green();
    blue = -1*awayTeamMain.blue() *NAME_GRADIENT_LEVEL + awayTeamMain.blue();
    end.setRgb(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    //awayNameGradient.setColorAt(0.45, awayTeamMain);
    awayNameGradient.setColorAt(0, awayTeamMain);
    awayNameGradient.setColorAt(1, end);
    //awayNameGradient.setColorAt(0, end);

    red = -1*awayTeamMain.red() *STAT_GRADIENT_LEVEL + awayTeamMain.red();
    green = -1*awayTeamMain.green() *STAT_GRADIENT_LEVEL + awayTeamMain.green();
    blue = -1*awayTeamMain.blue() *STAT_GRADIENT_LEVEL + awayTeamMain.blue();
    end.setRgb(red, green, blue);
    if (end == QColor(0,0,0))
        end = QColor(1,1,1);
    awayStatGradient.setColorAt(0, awayTeamMain);
    awayStatGradient.setColorAt(1, end);
    //awayStatGradient.setColorAt(0, end);


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
    while (fontSize.width(statistics[0]) > this->rect().width() - NAME_WIDTH) {
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
