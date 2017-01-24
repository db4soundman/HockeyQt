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
#include "GraphicChooser.txt"

class ComparisonGraphic : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    ComparisonGraphic(QColor awayColor, QColor homeColor, QPixmap pawayLogo);
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);



public slots:
    void hideComparison();
    void showComparison();
    void prepareComp(QString awayName, QString awayLabel, QString homeName, QString homeLabel, QList<QString> stats, QString pstatHeader="");

private:
    QList<QString> statNames;
    QList<QString> statistics;

    QFont statFont, nameFont, labelFont;
    QLinearGradient statHeaderGradient, bgGradient, homeStatGradient, awayStatGradient;
    QColor homeTeamMain, awayTeamMain, stats;

    QString homeName, awayName, homeLabel, awayLabel, homeStat, awayStat, statHeader;

    QPixmap *homeLogo, *awayLogo;

    void prepareColors();
    void prepareFontSize();
    //void adjustFont();

    bool show;
    int fontPointSize, statFontPointSize, awayLogoOffset;
};


#endif // COMPARISONGRAPHIC_H
