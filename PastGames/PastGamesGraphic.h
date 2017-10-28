#ifndef PASTGAMESGRAPHIC_H
#define PASTGAMESGRAPHIC_H

#include <QGraphicsRectItem>
#include <QList>
#include <QPainter>
#include <QLinearGradient>
#include <QPixmap>
#include <QColor>
#include "GameHistory.h"
#include "HockeyTeam.h"

class PastGamesGraphic : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    PastGamesGraphic(HockeyTeam* hTeam, HockeyTeam* aTeam, QGraphicsItem* parent = 0);

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

signals:
    void addNoTransparencyZone(QRect r);
    void removeNoTransparencyZone(QRect r);

public slots:
    void toggleShow();
    void hide();
    void receiveData(bool team, int num);

private:

    bool show, homeTeam;
    QLinearGradient border, background, teamBg;
    QList<GameHistory> gameHistory, awayHistory, homeHistory;
    QPixmap homeLogo, awayLogo;
    QColor homeColor, awayColor;
    QString homeName, awayName;
    int numToShow;

};


#endif // PASTGAMESGRAPHIC_H
