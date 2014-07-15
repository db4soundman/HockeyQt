#ifndef STANDINGSGRAPHIC_H
#define STANDINGSGRAPHIC_H

#include <QGraphicsPixmapItem>
#include "StandingsEntry.h"
#include <QList>
#include <QPainter>

class StandingsGraphic : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    StandingsGraphic(QGraphicsItem* parent = 0);

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

public slots:
    void updateStandings(QList<StandingsEntry> list);
    void toggleShow();
    void hide();

private:
    QList<StandingsEntry> nchcStandings;
    bool show;
};

#endif // STANDINGSGRAPHIC_H
