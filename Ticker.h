#ifndef TICKER_H
#define TICKER_H

#include <QGraphicsRectItem>
#include <QList>
#include <QLinearGradient>
#include "HockeyPlayer.h"
#include <QTimer>
#include "NchcScoreEntry.h"
#include <QPainter>

class Ticker : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Ticker();

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    void setFridayGames(const QList<NchcScoreEntry>& value);
    void setSaturdayGames(const QList<NchcScoreEntry>& value);

public slots:
    void advanceTicker();
    void showTicker();
    void hideTicker();

private:
    QList<NchcScoreEntry> games;
    void prepareColor();
    QFont resizeText();
    int width;
    int index;
    //QList<HockeyGame*> players;
    QLinearGradient mainGradient;
    bool show;
    QTimer timer;
};

#endif // TICKER_H
