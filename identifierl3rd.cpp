#include "identifierl3rd.h"

#define NAME_HEIGHT 40
#define TWITTER_HEIGHT 30
#define HEIGHT NAME_HEIGHT + TWITTER_HEIGHT
#define WIDTH 1100

#include <algorithm>
#include <QFont>
#include <QGraphicsScene>

IdentifierL3rd::IdentifierL3rd()
{
    setRect(QRect(0,0,X, HEIGHT));
}

void IdentifierL3rd::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (show) {
        painter->fillRect(0,0,WIDTH,HEIGHT,secondaryGradient);
        painter->fillRect(1,1,WIDTH-2, NAME_HEIGHT-2, primaryGradient);
        int numSections = max(names.size(), twitterData.size());
        int sectionWidth = WIDTH / numSections;

        painter->setPen(QColor(240,240,240));
        painter->setFont(QFont("Arial", 20, QFont::Bold));
        // Slot 1
        painter->drawText(0,0,sectionWidth, NAME_HEIGHT, Qt::AlignCenter, names[0]);
        // Slot 2
        if (names.size() == 3) {
            painter->drawText(sectionWidth,0,sectionWidth, NAME_HEIGHT, Qt::AlignCenter, names[1]);
            painter->drawText(sectionWidth*2,0,sectionWidth, NAME_HEIGHT, Qt::AlignCenter, names[2]);
        } else {
            painter->drawText(sectionWidth*2,0,sectionWidth, NAME_HEIGHT, Qt::AlignCenter, names[1]);
        }


        // Twitter stuff
        painter->setPen(QColor(1,1,1));
        painter->setFont(QFont("Arial", 16));
        // Slot 1
        painter->drawText(0,0,sectionWidth, NAME_HEIGHT, Qt::AlignCenter, twitterData[0]);
        // Slot 2
        if (twitterData.size() == 3) {
            painter->drawText(sectionWidth,NAME_HEIGHT,sectionWidth, TWITTER_HEIGHT, Qt::AlignCenter, twitterData[1]);
            painter->drawText(sectionWidth*2,NAME_HEIGHT,sectionWidth, TWITTER_HEIGHT, Qt::AlignCenter, twitterData[2]);
        } else {
            painter->drawText(sectionWidth*2,NAME_HEIGHT,sectionWidth, TWITTER_HEIGHT, Qt::AlignCenter, twitterData[1]);
        }
    }
}

int IdentifierL3rd::getWidth()
{
    return WIDTH;
}

int IdentifierL3rd::getHeight()
{
    return HEIGHT;
}

void IdentifierL3rd::showId(QStringList names, QStringList twitterData)
{
    this->names = names;
    this->twitterData = twitterData;
    show = true;
    scene()->update(x(), y(), WIDTH, HEIGHT);
}

void IdentifierL3rd::hideId()
{
    if (show) {
        show = false;
        scene()->update(x(), y(), WIDTH, HEIGHT);
    }
}

void IdentifierL3rd::prepareColors()
{
    secondaryGradient.setStart(0,0);
    secondaryGradient.setFinalStop(0, HEIGHT);
    secondaryGradient.setColorAt(0, QColor(196, 213, 242));
    secondaryGradient.setColorAt(1, QColor(196, 213, 242));

    primaryGradient.setStart(0,0);
    primaryGradient.setFinalStop(0, HEIGHT);
    primaryGradient.setColorAt(0, QColor(41, 70, 91));
    primaryGradient.setColorAt(1, QColor(23, 41, 53));
}
