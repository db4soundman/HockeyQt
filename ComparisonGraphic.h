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
    ComparisonGraphic(QColor awayColor, QColor homeColor, QPixmap pawayLogo, bool preview=false);
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    void paintPreview(QPainter* painter);

    int getWidth();
    int getHeight();


public slots:
    void hideComparison();
    void showComparison();
    void prepareComp(QString topLabel, QString botLabel, QList<QString> stats, QString pStatHeader, int compStyle);
    void prepareStandardComp(QString awayLabel, QString homeLabel, QList<QString> stats, QString pstatHeader="");

private:
    QList<QString> statNames;
    QList<QString> statistics;

    QFont statFont, nameFont, labelFont;
    QLinearGradient statHeaderGradient, bgGradient, topGradient, bottomGradient;
    QColor homeTeamMain, homeGradientEnd, awayTeamMain, awayGradientEnd, stats;

    QString homeName, awayName, homeLabel, awayLabel, homeStat, awayStat, statHeader;

    QPixmap *homeLogo, *awayLogo;

    void prepareColors();
    void prepareFontSize();
    //void adjustFont();

    bool show, topOffset, botOffset, preview;
    int fontPointSize, statFontPointSize, awayLogoXOffset, awayLogoYOffset;
};


#endif // COMPARISONGRAPHIC_H
