#ifndef SCHEDULEGRAPHIC_H
#define SCHEDULEGRAPHIC_H

#include "scheduleentry.h"
#include <QGraphicsRectItem>
#include <QList>
#include <QPainter>
#include <QLinearGradient>
#include <QImage>
#include <QPixmap>

class ScheduleGraphic : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    ScheduleGraphic(QGraphicsItem* parent = 0);

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    void setCanvas(QImage *value);

public slots:
    void toggleShow();
    void hide();
    void receiveData(QList<ScheduleEntry> sched, bool seriesSched);

private:

    QPixmap &getPixmap(QString logo);
    void draw(QPainter* painter);

    bool show, seriesMode;
    QLinearGradient border, background;
    QPixmap nchc, cbs, twc, asn, none;
    QImage* canvas;
    QList<ScheduleEntry> schedule;
};


#endif // SCHEDULEGRAPHIC_H
