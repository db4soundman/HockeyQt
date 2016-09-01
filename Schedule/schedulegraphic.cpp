#include "schedulegraphic.h"
#include <QFont>
#include "MiamiAllAccessHockey.h"
#include <QGraphicsScene>

#define WIDTH 330
#define HEIGHT 500


ScheduleGraphic::ScheduleGraphic(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    setRect(0,0,WIDTH,HEIGHT);
    border.setStart(0,0);
    border.setFinalStop(WIDTH, HEIGHT);
    border.setColorAt(0, QColor(50,50,50));
    border.setColorAt(.5, QColor(80,80,80));
    border.setColorAt(1, QColor(50,50,50));

    background.setStart(0,0);
    background.setFinalStop(WIDTH, HEIGHT);
    background.setColorAt(0, QColor(10,10,10));
    background.setColorAt(1, QColor(20,20,20));
    //background.setColorAt(1, QColor(10,10,10));
    show = false;

    nchc = MiamiAllAccessHockey::getImgFromResources(":/images/NCHCTV.png", 20);
    twc = MiamiAllAccessHockey::getImgFromResources(":/images/TWC.png", 20);
    cbs = MiamiAllAccessHockey::getImgFromResources(":/images/CBSSN.png", 20);
    asn = MiamiAllAccessHockey::getImgFromResources(":/images/ASN.png", 20);
    none = MiamiAllAccessHockey::getImgFromResources(":/images/NOLOGO.png", 20);

}

void ScheduleGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (show) {
        painter->fillRect(rect(), border);
        painter->fillRect(10,10, WIDTH-20, HEIGHT-20, background);
        QFont font("Arial", 12);
        painter->setPen(QColor(253,180,26));
        if (seriesMode) {
            painter->drawText(230, 15, 30, 30,0,"Game 1");
            painter->drawText(290, 15, 30, 30,0,"Game 2");
        }
        painter->setPen(QColor(255,255,255));
        painter->setFont(font);
        for (int i = 0; i < schedule.size(); i++) {
            int y = 30 * (i+1);
            painter->drawText(15, y, 60, 30, 0, schedule[i].getNumGames() == 2 ?
                                  schedule[i].getMonth1() + "/" + schedule[i].getMonth2() :
                                  schedule[i].getMonth1());
            painter->drawText(75, y, 40, 30, 0, schedule[i].getNumGames() == 2 ?
                                  schedule[i].getDate1() + "/" + schedule[i].getDate2() :
                                  schedule[i].getDate1());
            painter->drawText(115,y, 25, 30, 0, schedule[i].getVsAt());
            painter->drawText(140,y, 80, 30, 0, schedule[i].getOpp());
            if (seriesMode) {
                painter->drawText(230, y, 30, 30, 0, schedule[i].getTime1() + " / ");
                painter->drawPixmap(260, y, 30, 30, getPixmap(schedule[i].getMedia1()));
                if (schedule[i].getNumGames() == 2) {
                    painter->drawText(290, y, 30, 30, 0, schedule[i].getTime2() + " / ");
                    painter->drawPixmap(320, y, 30, 30, getPixmap(schedule[i].getMedia2()));
                }
            }
            else {
                painter->drawText(230, y, 30, 30, 0, schedule[i].getTime1());
                painter->drawPixmap(260, y, 30, 30, getPixmap(schedule[i].getMedia1()));
            }
        }
    }
}

void ScheduleGraphic::toggleShow()
{
    show = true;
    scene()->update(x(), y(), WIDTH, HEIGHT);
}

void ScheduleGraphic::hide()
{
    if (show) {
        show = false;
        scene()->update(x(), y(), WIDTH, HEIGHT);
    }
}

void ScheduleGraphic::receiveData(QList<ScheduleEntry> sched)
{
    schedule=sched;
}

QPixmap &ScheduleGraphic::getPixmap(QString logo)
{
    if (logo == "CBSSN") return cbs;
    if (logo == "TWC") return twc;
    if (logo == "ASN") return asn;
    if (logo == "NCHC.TV") return nchc;
    return none;
}
