#ifndef IDENTIFIERL3RD_H
#define IDENTIFIERL3RD_H

#include <QObject>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QLinearGradient>
#include <QStringList>
#include <QPainter>

class IdentifierL3rd: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    IdentifierL3rd();


    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    void paintPreview(QPainter* painter);

    int getWidth();
    int getHeight();


signals:
    void addNoTransparencyZone(QRect r);
    void removeNoTransparencyZone(QRect r);

public slots:
    void showId(QStringList names, QStringList twitterData);
    void hideId();

private:
    void prepareColors();
    void prepareFontSize();
    void adjustFont();
    bool show;
    QLinearGradient primaryGradient, secondaryGradient;
    QStringList names, twitterData;
};

#endif // IDENTIFIERL3RD_H
