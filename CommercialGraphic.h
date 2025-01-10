#ifndef COMMERCIALGRAPHIC_H
#define COMMERCIALGRAPHIC_H

#include <QGraphicsRectItem>
#include <QPixmap>
#include <QFont>
#include "HockeyGame.h"
#include <QLinearGradient>
#include <QPainter>
#include <QGraphicsTextItem>
#include <QRect>
#include "GraphicChooser.txt"
class CommercialGraphic : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
#ifdef GRADIENT_LOOK
    CommercialGraphic(HockeyGame* game, int width, QString pawayLogo, QGraphicsItem *parent = 0);
#else
    CommercialGraphic(HockeyGame* game, QGraphicsItem *parent = 0);
#endif
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    int getWidth();
    int getHeight();

signals:
    void addNoTransparencyZone(QRect r);
    void removeNoTransparencyZone(QRect r);

public slots:
    void prepareAndShow();
    void updateClock();
    void showClock();
    void intermissionTime();
    void finalTime();
    void hide();
    void changeUseClock(bool uc);
    void toggleAwayLogoBg(bool on);

private:
    QPixmap networkLogo;
    QLinearGradient homeTeamGradient, awayTeamGradient, clockGradient, bgGradient;
    HockeyGame* hockeyGame;
    bool show, inGame, useClock, altAwayLogoBg;
    QGraphicsTextItem* away, *home;
    QString homeScore, awayScore, networkText, period, clock;
    QFont descriptiveFont;
    int clockStatus, awayLogoHeightOffset, awayLogoWidthOffset, homeLogoWidthOffset;
    void checkAwayFont();
    void prepareGradients(QColor awayColor, QColor homeColor);
    QPixmap homeLogo, *awayLogo;
#ifdef GRADIENT_LOOK
    int WIDTH, NAME_WIDTH;
#endif
    // yep, a test
};

#endif // COMMERCIALGRAPHIC_H
