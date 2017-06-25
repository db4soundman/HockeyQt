#ifndef NCHCSCOREBOARDGRAPHIC_H
#define NCHCSCOREBOARDGRAPHIC_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QObject>
#include <QLinearGradient>
#include "NchcScoreEntry.h"

class NchcScoreboardGraphic : public QObject, public QGraphicsRectItem {
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

public slots:
    void showImg();
    void hide();

private:
    QList<NchcScoreEntry> fridayGames, saturdayGames;
    QLinearGradient mainGradient;
    QPixmap* nchcLogo;
    bool show;
    QString leftHeader, rightHeader;
};

#endif // NCHCSCOREBOARDGRAPHIC_H
