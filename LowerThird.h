#ifndef LOWERTHIRD_H
#define LOWERTHIRD_H

#include <QGraphicsPixmapItem>
#include <QLinearGradient>
#include <QPainter>
#include <QObject>
#include <QList>
#include <QString>
#include <QFont>
#include <QColor>

class LowerThird : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    LowerThird(QGraphicsItem* parent = 0);

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);



public slots:
    void hideLt();
    void showLt();
    void prepareForDisplay(QString name, QString number, QString year, QList<QString> statLabels,
                           QList<QString> statValues, QColor teamColor);
private:
    QList<QString> statNames;
    QList<QString> statistics;
    QString name, number, year, firstName, lastName;
    QFont statFont, nameFont;
    QLinearGradient gradient, statGradient;
    QColor defaultColor;

    void prepareColor();
    void prepareFontSize();

    bool show;
    int fontPointSize;
};

#endif // LOWERTHIRD_H
