#include "schedulegraphic.h"
#include <QFont>
#include "MiamiAllAccessHockey.h"
#include <QGraphicsScene>

#define WIDTH 700
#define HEIGHT 300


ScheduleGraphic::ScheduleGraphic(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    setRect(0,0,WIDTH,HEIGHT);
    border.setStart(0,0);
    border.setFinalStop(0, HEIGHT);
    border.setColorAt(0, QColor(196, 213, 242));
    border.setColorAt(1, QColor(196, 213, 242));

    background.setStart(0,0);
    background.setFinalStop(0, HEIGHT);
    background.setColorAt(0, QColor(41, 70, 91));
    background.setColorAt(1, QColor(23, 41, 53));
    //background.setColorAt(1, QColor(10,10,10));
    show = false;

    nchc = MiamiAllAccessHockey::getImgFromResources(":/images/NCHCTV.png", 20, 500);
    twc = MiamiAllAccessHockey::getImgFromResources(":/images/TWC.png", 20, 500);
    cbs = MiamiAllAccessHockey::getImgFromResources(":/images/CBSSN.png", 20, 500);
    asn = MiamiAllAccessHockey::getImgFromResources(":/images/ASN.png", 20,500);
    none = MiamiAllAccessHockey::getImgFromResources(":/images/NOLOGO.png", 2);
    seriesMode = true;
}

void ScheduleGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (show) {
        QRectF graphicRect = rect();
        if (!seriesMode) {
            graphicRect.setWidth(520);
        }
        graphicRect.setHeight(30 * (schedule.size()+1) + 30);
        painter->fillRect(graphicRect, border);
        painter->fillRect(4,4, graphicRect.width()-8, graphicRect.height()-8, background);
        QFont headerFont("Arial", 16);
        painter->setPen(QColor(253,180,26));
        painter->setFont(headerFont);
        painter->drawText(0,10, graphicRect.width(), 20, Qt::AlignHCenter, "UPCOMING SCHEDULE");
        QFont font("Arial", 12);
        painter->setFont(font);
        if (seriesMode) {
            painter->drawText(350, 35, 60, 30,0,"Game 1");
            painter->drawText(520, 35, 60, 30,0,"Game 2");
        }
        painter->setPen(QColor(255,255,255));
        for (int i = 0; i < schedule.size(); i++) {
            int y = 30 * (i+1) + 30;
            if (schedule[i].getNumGames() == 0) continue;
            painter->drawText(15, y, 60, 30, 0, schedule[i].getNumGames() == 2 && (!schedule[i].getMonth2().isEmpty() &&
                                                                                   schedule[i].getMonth2() != schedule[i].getMonth1())?
                                  schedule[i].getMonth1() + "/" + schedule[i].getMonth2() :
                                  schedule[i].getMonth1());
            painter->drawText(75, y, 40, 30, 0, schedule[i].getNumGames() == 2 && seriesMode?
                                  schedule[i].getDate1() + "/" + schedule[i].getDate2() :
                                  schedule[i].getDate1());
            painter->drawText(125,y, 25, 30, 0, schedule[i].getVsAt());
            painter->drawText(160,y, 180, 30, 0, schedule[i].getOpp());
            if (seriesMode) {
                painter->drawText(350, y, 60, 30, 0, schedule[i].getTime1());
                QPixmap logo1 = getPixmap(schedule[i].getMedia1());
                painter->drawPixmap(420, y, logo1.width(), logo1.height(), logo1);
                if (schedule[i].getNumGames() == 2) {
                    painter->drawText(520, y, 60, 20, 0, schedule[i].getTime2());
                    QPixmap logo2 = getPixmap(schedule[i].getMedia2());
                    painter->drawPixmap(580, y, logo2.width(), logo2.height(), logo2);
                }
            }
            else {
                painter->drawText(350, y, 60, 30, 0, schedule[i].getTime1());
                QPixmap logo1 = getPixmap(schedule[i].getMedia1());
                painter->drawPixmap(420, y, logo1.width(), logo1.height(), logo1);
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

void ScheduleGraphic::receiveData(QList<ScheduleEntry> sched, bool seriesSched)
{
    schedule=sched;
    seriesMode=seriesSched;
}

QPixmap &ScheduleGraphic::getPixmap(QString logo)
{
    if (logo == "CBSSN") return cbs;
    if (logo == "TWC") return twc;
    if (logo == "ASN") return asn;
    if (logo == "NCHC.TV") return nchc;
    return none;
}
