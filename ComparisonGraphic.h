#ifndef COMPARISONGRAPHIC_H
#define COMPARISONGRAPHIC_H

#include <QGraphicsRectItem>
#include <QLinearGradient>
#include <QPainter>
#include <QObject>
#include <QList>
#include <QString>
#include <QFont>
#include <QColor>
#include <QImage>
#include "GraphicChooser.txt"

class ComparisonGraphic : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    ComparisonGraphic(QColor awayColor, QColor homeColor, QPixmap pawayLogo);
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);



    void setCanvas(QImage *value);

public slots:
    void hideComparison();
    void showComparison();
    void prepareComp(QString awayLabel, QString homeLabel, QList<QString> stats, QString pstatHeader="");

private:
    QList<QString> statNames;
    QList<QString> statistics;
    QImage *canvas;
    QFont statFont, nameFont, labelFont;
    QLinearGradient statHeaderGradient, bgGradient, homeStatGradient, awayStatGradient;
    QColor homeTeamMain, awayTeamMain, stats;

    QString homeName, awayName, homeLabel, awayLabel, homeStat, awayStat, statHeader;

    QPixmap *homeLogo, *awayLogo;

    void prepareColors();
    void prepareFontSize();
    void draw(QPainter* painter);
    //void adjustFont();

    bool show;
    int fontPointSize, statFontPointSize, awayLogoOffset;
};


#endif // COMPARISONGRAPHIC_H
