#include "LowerThird.h"
#include <QFontMetrics>
#include <QStringRef>
#include <QGraphicsScene>

#define NAME_GRADIENT_LEVEL .7
#define STAT_GRADIENT_LEVEL .7
#define NAME_WIDTH 310
LowerThird::LowerThird(QGraphicsItem* parent) : QGraphicsPixmapItem(parent),
    name(""), number("number"), statFont("Arial", 36, QFont::Bold), nameFont("Arial", 36, QFont::Bold) {

    setPixmap(QPixmap(":/images/LowerThird.png"));
    gradient.setStart(0, 0);
    gradient.setFinalStop(0, 120);
    statGradient.setStart(0, 48);
    statGradient.setFinalStop(0, 120);
    defaultColor = QColor(220, 0, 0);
    prepareColor();
    statistics.append("");
    statNames.append("");
    show = false;
}

void
LowerThird::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (show) {
        painter->drawPixmap(0, 0, this->pixmap());
        painter->fillRect(-372, 0, 372, 120, gradient);
        painter->fillRect(0, 47, 800, 72, statGradient);
        painter->fillRect(0, 47, 800, 72, QColor(0, 0, 0, 60));

        painter->setFont(nameFont);
        painter->setPen(QColor(255,255,255));
        painter->drawText(-370, 0, NAME_WIDTH, 120, Qt::AlignVCenter, firstName + "\n" + lastName);
        painter->drawText(-60, 0, 60, 60, Qt::AlignCenter, number);
        painter->drawText(-60, 60, 60, 60, Qt::AlignCenter, year);

        // Stat numbers
        int rectWidth = 800/statistics.size();
        for (int i = 0; i< statistics.size(); i++) {
            painter->drawText(rectWidth * i, 47, rectWidth, 72, Qt::AlignCenter, statistics.at(i));
        }
        // Stat Labels
        painter->setPen(QColor(0, 0, 0));
        for (int i = 0; i< statNames.size(); i++) {
            painter->drawText(rectWidth * i, 0, rectWidth, 47, Qt::AlignCenter, statNames.at(i));
        }
    }
}

void
LowerThird::prepareForDisplay(QString name, QString number, QString year,
                              QList<QString> statLabels,
                              QList<QString> statValues, QColor teamColor) {
    this->name = name;
    firstName = name.left(name.indexOf(" "));
    QStringRef substr(&name, name.indexOf(" ") + 1, name.length() - (name.indexOf(" ")+1));
    lastName = substr.toString();
    this->year = year;
    this->number = number;
    statNames = statLabels;
    statistics = statValues;
    defaultColor = teamColor;
    prepareColor();
    prepareFontSize();
    showLt();
}

void
LowerThird::prepareColor() {
    int red, green, blue;
    red = -1*defaultColor.red() *NAME_GRADIENT_LEVEL + defaultColor.red();
    green = -1*defaultColor.green() *NAME_GRADIENT_LEVEL + defaultColor.green();
    blue = -1*defaultColor.blue() *NAME_GRADIENT_LEVEL + defaultColor.blue();

    QColor end(red, green, blue);
    gradient.setColorAt(0.45, defaultColor);
    gradient.setColorAt(0.55, defaultColor);
    gradient.setColorAt(1, end);
    gradient.setColorAt(0, end);

    red = -1*defaultColor.red() *STAT_GRADIENT_LEVEL + defaultColor.red();
    green = -1*defaultColor.green() *STAT_GRADIENT_LEVEL + defaultColor.green();
    blue = -1*defaultColor.blue() *STAT_GRADIENT_LEVEL + defaultColor.blue();
    QColor end2(red, green, blue);
    statGradient.setColorAt(.5, defaultColor);
    statGradient.setColorAt(1, end2);
    statGradient.setColorAt(0, end2);

}

void
LowerThird::prepareFontSize() {
    int subtraction = 1;
    QFontMetrics fontSize(nameFont);
    while (fontSize.width(firstName) > NAME_WIDTH ||
           fontSize.width(lastName) > NAME_WIDTH) {
        nameFont.setPointSize(36 - subtraction);
        subtraction++;
        QFontMetrics temp(nameFont);
        fontSize = temp;
    }
}

void
LowerThird::hideLt() {
    show = false;
    scene()->update();
}

void
LowerThird::showLt() {
    show = true;
    scene()->update();
}
