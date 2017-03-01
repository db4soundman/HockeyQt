#ifndef NCHCSCOREBOARDGRAPHIC_H
#define NCHCSCOREBOARDGRAPHIC_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QObject>
#include <QImage>
#include "NchcScoreEntry.h"

class NchcScoreboardGraphic : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    NchcScoreboardGraphic();

    QList<NchcScoreEntry> getScores() const;
    void setScores(const QList<NchcScoreEntry> value);

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    QList<NchcScoreEntry> getFridayGames() const;
    void setFridayGames(const QList<NchcScoreEntry>& value);

    QList<NchcScoreEntry> getSaturdayGames() const;
    void setSaturdayGames(const QList<NchcScoreEntry>& value);


    void setLeftHeader(const QString &value);

    void setRightHeader(const QString &value);

    void setCanvas(QImage *value);

public slots:
    void showImg();
    void hide();

private:
    QList<NchcScoreEntry> fridayGames, saturdayGames;
    QPixmap* nchcLogo;
    QImage* canvas;
    bool show;
    QString leftHeader, rightHeader;
    void draw(QPainter* painter);
};

#endif // NCHCSCOREBOARDGRAPHIC_H
